#pragma once
#include "CommandExecutionResult.h"
#include <functional>

#include "Callbacks.h"
#include "RuntimeContext.h"

class BindedCommand
{
public:
    BindedCommand() {}
    ~BindedCommand() {}

    void Execute(Callback callback = nullptr);

    CommandExecutionResult Result() const noexcept;

private:
    CommandExecutionResult m_result;
    RuntimeContext* m_context;
};
