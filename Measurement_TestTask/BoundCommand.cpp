﻿#include "BoundCommand.h"

void BoundCommand::Execute()
{
    switch(m_type)
    {
    case ci_point:
    case ci_move:
    case ci_comment:
        m_command->Execute(m_args);
    case ci_circle:
    case ci_plane:
    case ci_project:
    case ci_circle_diff:
    case ci_circle_to_point:
    case ci_point_diff:
        m_command->Execute(m_alt_args);

    case ci_undefined:
        break;
    }
}

CommandBase* BoundCommand::GetCommandObject() const noexcept
{
    return m_command;
}


CommandExecutionResult BoundCommand::Result() const noexcept
{
    return m_result;
}
