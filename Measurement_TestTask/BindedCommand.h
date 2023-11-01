#pragma once
#include "CommandBase.h"
#include "CommandExecutionResult.h"
#include "RuntimeContext.h"

class BindedCommand
{
public:
    BindedCommand(CommandBase* command, const std::vector<double>& args, const std::vector<ContextObject*> alternate_args)
    {
        m_command = command;
        m_args = args;
        m_alt_args = alternate_args;
    }
    ~BindedCommand() = default;

    void Execute();

    CommandExecutionResult Result() const noexcept;

private:
    CommandBase* m_command;
    std::vector<double> m_args;
    std::vector<ContextObject*> m_alt_args;
    ContextObjectType m_type;

    CommandExecutionResult m_result;
    RuntimeContext* m_context;
};
