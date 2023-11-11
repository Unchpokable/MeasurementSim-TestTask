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

    BoundCommand& operator=(BoundCommand&& other) noexcept
    {
        if (this != &other)
        {
            m_command = other.m_command;
            m_args = std::move(other.m_args);
            m_alt_args = std::move(other.m_alt_args);
            m_type = other.m_type;

            m_result = other.m_result;
            m_context = other.m_context;
        }
        return *this;
    }

    ~BoundCommand()
    {
    }

    void Execute();
    CommandBase* GetCommandObject() const noexcept;
    CommandExecutionResult Result() const noexcept;

    QString ToString() const noexcept;
    QString ToPrettyString() const noexcept {
        return m_command->ToPrettyString();
    }

    const std::vector<ContextObject*>& GetDependencies() const noexcept;

private:
    CommandBase* m_command;
    std::vector<double> m_args;
    std::vector<ContextObject*> m_alt_args;
    ContextObjectType m_type;

    CommandExecutionResult m_result;
    RuntimeContext* m_context;
};
