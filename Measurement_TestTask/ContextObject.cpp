#include "ContextObject.h"

bool ContextObject::IsEquals(const ContextObject& other) const noexcept
{
    return m_object_name == other.m_object_name && m_type == other.m_type;
}


QString ContextObject::GetName() const noexcept
{
    return m_object_name;
}

ContextObjectType ContextObject::GetType() const noexcept
{
    return m_type;
}

void ContextObject::SetType(ContextObjectType type)
{
    m_type = type;
}


