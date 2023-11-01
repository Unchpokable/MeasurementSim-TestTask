#include "CommandInterpreter.h"

#include "CommandBase.h"

CommandInterpreter::CommandInterpreter() noexcept
    : m_mutex()
{
    m_exec_context = new RuntimeContext();
}

void CommandInterpreter::AddCommand(CommandBase* command, const std::vector<double>& args)
{
    const auto contextObj = dynamic_cast<ContextObject*>(command);

    if(contextObj == nullptr)
        throw std::exception("Invalid parameter: Given object is not ContextObject pointer");

    m_exec_context->AddObject(contextObj);
}

void CommandInterpreter::AddCommand(CommandBase* command, const std::vector<ContextObject*>& args)
{
    const auto contextObj = dynamic_cast<ContextObject*>(command);

    if(contextObj == nullptr)
        throw std::invalid_argument("Invalid parameter: Given object is not ContextObject pointer");

    m_exec_context->AddObject(contextObj);
}

