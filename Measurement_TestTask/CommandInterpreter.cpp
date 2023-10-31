#include "CommandInterpreter.h"

CommandInterpreter::CommandInterpreter() noexcept
    : m_mutex()
{
    m_exec_context = new RuntimeContext();
}

void CommandInterpreter::AddCommand(CommandBase* command)
{
    auto contextObj = dynamic_cast<ContextObject*>(command);

    if(contextObj == nullptr)
        throw std::exception("Invalid parameter: Given object is not ContextObject pointer");

    m_exec_context->AddObject(contextObj);
}


