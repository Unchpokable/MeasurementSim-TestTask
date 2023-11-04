#include "AddCommandBase.h"

AddCommandBase::AddCommandBase(RuntimeContext* context)
{
    if(context)
        m_runtime_context = context;
    m_constructed_command = nullptr;
}

AddCommandBase::~AddCommandBase() = default;

void AddCommandBase::ConstructCommandObject()
{
    throw std::exception("Method not implemented");
}

const BoundCommand* AddCommandBase::GetConstructedObject() const noexcept
{
    return m_constructed_command;
}




