#include "CommandInterpreter.h"
#include "BindedCommand.h"
#include "CommandBase.h"

CommandInterpreter::CommandInterpreter() noexcept
    : m_mutex()
{
    m_commands = new std::vector<BindedCommand*>();
    m_exec_context = new RuntimeContext();
}

void CommandInterpreter::AddCommand(CommandBase* command, const std::vector<double>& args)
{
    AddToContext(command);
    std::vector<ContextObject*> dummy {};
    auto binded_command = new BindedCommand(m_exec_context, command, args, dummy);
    m_commands->push_back(binded_command);
}

void CommandInterpreter::AddCommand(CommandBase* command, const std::vector<ContextObject*>& args)
{
    AddToContext(command);
    std::vector<double> dummy {};
    auto binded_command = new BindedCommand(m_exec_context, command, dummy, args);
    m_commands->push_back(binded_command);
}

void CommandInterpreter::AddToContext(CommandBase* who)
{
    const auto contextObj = dynamic_cast<ContextObject*>(who);

    if(contextObj == nullptr)
        throw std::invalid_argument("Invalid parameter: Given object is not ContextObject pointer");

    m_exec_context->AddObject(contextObj);
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
        m_mutex.lock();
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
        m_mutex.unlock();
    });
}

const RuntimeContext* CommandInterpreter::GetContext() const noexcept
{
    return m_exec_context;
}
