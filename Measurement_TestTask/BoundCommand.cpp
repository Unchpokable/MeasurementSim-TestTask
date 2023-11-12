#include "BoundCommand.h"

void BoundCommand::Execute()
{
    switch(m_type)
    {
    case ci_point:
    case ci_move:
    case ci_comment:
        {
            m_command->Execute(m_args);
            break;
        }
    case ci_circle:
    case ci_plane:
    case ci_project:
    case ci_circle_diff:
    case ci_circle_to_point:
    case ci_point_diff:
        {
            m_command->Execute(m_alt_args);
            break;
        }
    case ci_undefined:
        break;
    }

    m_result = ce_success;
}

CommandBase* BoundCommand::GetCommandObject() const noexcept
{
    return m_command;
}

const std::vector<ContextObject*>& BoundCommand::GetDependencies() const noexcept
{
    return m_alt_args;
}


CommandExecutionResult BoundCommand::Result() const noexcept
{
    return m_result;
}

QString BoundCommand::ToString() const noexcept
{
    return m_command->ToString();
}

void BoundCommand::UpdateArgs(const std::vector<ContextObject*>& args) noexcept
{
    m_alt_args = args;
}

void BoundCommand::UpdateArgs(const std::vector<double>& args) noexcept
{
    m_args = args;
}

std::vector<double> BoundCommand::GetArgs() const noexcept
{
    return m_args;
}

std::vector<ContextObject*> BoundCommand::GetCtxArgs() const noexcept
{
    return m_alt_args;
}


