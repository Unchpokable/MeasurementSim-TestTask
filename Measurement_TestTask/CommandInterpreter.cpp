#include "CommandInterpreter.h"
#include "BoundCommand.h"
#include "CommandBase.h"
#include "DefaultCallbacks.h"

CommandInterpreter::CommandInterpreter() noexcept
    : m_mutex()
{
    m_commands = new std::vector<BoundCommand*>();
    m_runtime_context = new RuntimeContext();
    m_shared_iterators = new std::vector<std::shared_ptr<CommandsIterWrapper>>();
}

bool CommandInterpreter::AddCommand(CommandBase* command, const std::vector<double>& args)
{
    const auto is_added_ctx = AddToContext(command);
    if(!is_added_ctx)
        return false;
    std::vector<ContextObject*> dummy {};
    const auto bound_command = new BoundCommand(m_runtime_context, command, args, dummy);
    m_commands->push_back(bound_command);
    InvalidateSharedIterators();

    return is_added_ctx;
}

bool CommandInterpreter::AddCommand(CommandBase* command, const std::vector<ContextObject*>& args)
{
    const auto is_added_ctx = AddToContext(command);
    if(!is_added_ctx)
        return false;

    if(!BindDependencies(dynamic_cast<ContextObject*>(command), args))
        return false;

    const std::vector<double> dummy {};
    const auto bound_command = new BoundCommand(m_runtime_context, command, dummy, args);
    m_commands->push_back(bound_command);
    InvalidateSharedIterators();

    return is_added_ctx;
}

void CommandInterpreter::AddCommand(BoundCommand* command)
{
    if(!AddToContext(command->GetCommandObject()))
        return;
    const auto ctx = dynamic_cast<ContextObject*>(command->GetCommandObject());

    const auto& deps = command->GetDependencies();
    if (!deps.empty())
    {
        if (!BindDependencies(ctx, deps))
        {
            m_runtime_context->RemoveObject(ctx->GetName());
            return;
        }
    }

    for (const auto dep: deps)
    {
        dep->AddTopLevelDependency(ctx);
    }

    m_commands->push_back(command);
    InvalidateSharedIterators();
}

bool CommandInterpreter::ReplaceCommand(BoundCommand* new_command, std::size_t position)
{
    if(position < 0 || position > m_commands->size())
        return false;

    const auto old_command = m_runtime_context->GetObjectByIndex(position);

    if(old_command == nullptr)
        return false;

    const auto ctx = dynamic_cast<ContextObject*>(new_command->GetCommandObject());
    m_runtime_context->ReplaceObject(position, ctx);

    const auto& deps = new_command->GetDependencies();
    if(!deps.empty())
    {
        if(!BindDependencies(ctx, deps))
        {
            m_runtime_context->ReplaceObject(position, old_command);
            return false;
        }
    }

    for (const auto dep: deps)
    {
        dep->RemoveTopLevelDependency(old_command);
        dep->AddTopLevelDependency(ctx);
    }

    delete old_command;

    const auto where = m_commands->begin() + position;
    const auto ptr = m_commands->at(position);
    delete ptr;
    *where = new_command;
    InvalidateSharedIterators();

    return true;
}

bool CommandInterpreter::RemoveCommand(std::size_t where)
{
    if(where < 0 || where >= m_commands->size())
        return false;

    const auto it = m_commands->begin();
    const auto ptr = m_commands->at(where);

    const auto cmd_deps = ptr->GetDependencies();

    for(const auto dep : cmd_deps)
        dep->RemoveTopLevelDependency(dynamic_cast<ContextObject*>(ptr->GetCommandObject()));

    m_commands->erase(it + where);
    delete ptr;
    m_runtime_context->RemoveObject(where);
    InvalidateSharedIterators();
    return true;
}

bool CommandInterpreter::InsertCommand(std::size_t where, BoundCommand* object)
{
    const auto it = m_commands->begin();

    if(where < 0 || where >= m_commands->size() || it + where >= m_commands->end())
        return false;

    const auto& deps = object->GetDependencies();
    const auto ctx = dynamic_cast<ContextObject*>(object->GetCommandObject());

    if(!m_runtime_context->InsertObject(where, ctx))
        return false;

    if(!deps.empty())
        if(!BindDependencies(ctx, deps))
            return false;

    for (const auto dep: deps)
    {
        dep->AddTopLevelDependency(ctx);
    }

    m_commands->insert(it + where, object);
    InvalidateSharedIterators();
    return true;
}

bool CommandInterpreter::AddToContext(CommandBase* who)
{
    const auto contextObj = dynamic_cast<ContextObject*>(who);

    if(contextObj == nullptr)
        throw std::invalid_argument("Invalid parameter: Given object is not ContextObject pointer");

    return m_runtime_context->AddObject(contextObj);
}

bool CommandInterpreter::BindDependencies(ContextObject* root, const std::vector<ContextObject*>& deps)
{
    return m_runtime_context->BindDependencies(root, deps);
}

std::shared_ptr<CommandsIterWrapper> CommandInterpreter::GetCommandsIterator() const noexcept
{
    auto out = std::make_shared<CommandsIterWrapper>();
    out->m_commandsBegin = m_commands->begin();
    out->m_commandsEnd = m_commands->end();
    out->m_commandsCurrent = out->m_commandsBegin;
    out->m_owner = this;

    m_shared_iterators->push_back(out);

    return out;
}

void CommandInterpreter::FreeIterator(const std::shared_ptr<CommandsIterWrapper>& iterator)
{
    const auto it = std::find(m_shared_iterators->begin(), m_shared_iterators->end(), iterator);
    if (it != m_shared_iterators->end())
    {
        (*it)->Invalidate();
        m_shared_iterators->erase(it);
    }
}

void CommandInterpreter::FreeIterator(CommandsIterWrapper* iterator)
{
    const auto it = std::find_if(m_shared_iterators->begin(), m_shared_iterators->end(),
        [iterator](const std::shared_ptr<CommandsIterWrapper>& _it) {
            return _it.get() == iterator;
    });

    if (it != m_shared_iterators->end())
    {
        (*it)->Invalidate();
        m_shared_iterators->erase(it);
    }
}


void CommandInterpreter::RunProgram() const
{
    for (const auto command: *m_commands)
    {
        command->Execute();
    }
}

const std::thread* CommandInterpreter::RunProgramAsync(const SingleArgumentCallback<QString>& post_exec_callback,
    const SingleArgumentCallback<QString>& error_callback) const
{
    return new std::thread([this, error_callback, post_exec_callback]() {
        for (const auto command: *m_commands)
        {
            try
            {
                command->Execute();
                post_exec_callback(command->ToPrettyString());
            }
            catch(const std::exception& ex)
            {
                error_callback(QString::fromUtf8(ex.what()));
                return;
            }
        }
    });
}

const RuntimeContext* CommandInterpreter::GetContext() const noexcept
{
    return m_runtime_context;
}

std::size_t CommandInterpreter::GetCommandsCount() const noexcept
{
    return m_commands->size();
}

const BoundCommand* CommandInterpreter::At(std::size_t position) const noexcept
{
    if(position < 0 || position >= m_commands->size())
        return nullptr;

    return m_commands->at(position);
}

void CommandInterpreter::InvalidateSharedIterators() const noexcept
{
    for (const auto& it: *m_shared_iterators)
    {
        it->Invalidate();
    }
}


const command_vec_iterator& CommandsIterWrapper::GetBegin() const
{
    if(!m_iter_wrapper_valid)
        throw std::exception("Source object was changed or iterator was freed");
    return m_commandsBegin;
}

const command_vec_iterator& CommandsIterWrapper::GetEnd() const
{
    if(!m_iter_wrapper_valid)
        throw std::exception("Source object was changed or iterator was freed");
    return m_commandsEnd;
}

command_vec_iterator& CommandsIterWrapper::GetCurrent() const
{
    if(!m_iter_wrapper_valid)
        throw std::exception("Source object was changed or iterator was freed");
    return const_cast<command_vec_iterator&>(m_commandsCurrent);
}

bool CommandsIterWrapper::MoveNext()
{
    if(m_commandsCurrent < m_commandsEnd)
    {
        ++m_commandsCurrent;
        return true;
    }
    return false;
}

void CommandsIterWrapper::Reset()
{
    m_commandsCurrent = m_commandsEnd;
}

void CommandsIterWrapper::Free()
{
    const_cast<CommandInterpreter*>(m_owner)->FreeIterator(this);
    m_iter_wrapper_valid = false;
}

bool CommandsIterWrapper::IsValid() const noexcept
{
    return m_iter_wrapper_valid;
}


void CommandsIterWrapper::Invalidate()
{
    m_iter_wrapper_valid = false;
}

