#pragma once
#include "BoundCommand.h"

class AddCommandBase
{
public:
    AddCommandBase(RuntimeContext* context);
    virtual ~AddCommandBase();
    const BoundCommand* GetConstructedObject() const noexcept;

protected:
    virtual void ConstructCommandObject();
    const BoundCommand* m_constructed_command;
    RuntimeContext* m_runtime_context;
};

