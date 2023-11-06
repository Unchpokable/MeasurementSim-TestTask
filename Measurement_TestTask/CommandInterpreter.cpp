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
    AddToContext(command->GetCommandObject());
    const auto ctx = dynamic_cast<ContextObject*>(command->GetCommandObject());

    const auto deps = command->GetDependencies();
    if (deps.empty())
        if (!BindDependencies(ctx, deps))
            return;

    m_commands->push_back(command);
    InvalidateSharedIterators();
}

bool CommandInterpreter::AddToContext(CommandBase* who)
{
    const auto contextObj = dynamic_cast<ContextObject*>(who);

    if(contextObj == nullptr)
        throw std::invalid_argument("Invalid parameter: Given object is not ContextObject pointer");

    return m_runtime_context->AddObject(contextObj, OnRuntimeContextCallback);
}

bool CommandInterpreter::BindDependencies(ContextObject* root, const std::vector<ContextObject*>& deps)
{
    const bool deps_bound = m_runtime_context->BindDependencies(root, deps);
    if(!deps_bound) 
    {
        m_runtime_context->RemoveObject(root->GetName(), OnRuntimeContextCallback);
        return false;
    }
    return true;
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

const std::thread* CommandInterpreter::RunProgramAsync(SingleArgumentCallback<QString> error_callback) const
{
    return new std::thread([this, error_callback]() {
        for (const auto command: *m_commands)
        {
            try
            {
                command->Execute();
            }
            catch(const std::exception& ex)
            {
                error_callback(QString::fromUtf8(ex.what()));
            }
        }
    });
}

const RuntimeContext* CommandInterpreter::GetContext() const noexcept
{
    return m_runtime_context;
}

void CommandInterpreter::InvalidateSharedIterators()
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

