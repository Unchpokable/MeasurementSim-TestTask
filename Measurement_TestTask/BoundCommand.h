#pragma once
#include "CommandBase.h"
#include "CommandExecutionResult.h"
#include "RuntimeContext.h"

class BoundCommand
{
public:
    BoundCommand(RuntimeContext* context, CommandBase* command, const std::vector<double>& args, const std::vector<ContextObject*>& alternate_args)
    {
        m_command = command;
        m_args = args;
        m_alt_args = alternate_args;
        m_context = context;

        const auto cmd_ctx = dynamic_cast<ContextObject*>(command);
        m_type = cmd_ctx->GetType();
        m_result = ce_not_started;
    }
    ~BoundCommand()
    {
        delete m_command;
    }

    void Execute();
    CommandBase* GetCommandObject() const noexcept;
    CommandExecutionResult Result() const noexcept;

    const std::vector<ContextObject*>& GetDependencies() const noexcept;

private:
    CommandBase* m_command;
    std::vector<double> m_args;
    std::vector<ContextObject*> m_alt_args;
    ContextObjectType m_type;

    CommandExecutionResult m_result;
    RuntimeContext* m_context;
};
