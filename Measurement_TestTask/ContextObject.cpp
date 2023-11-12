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

void ContextObject::AddDependentObject(const ContextObject* dep_obj)
{
    m_dependencies.push_back(const_cast<ContextObject*>(dep_obj));
}

const std::vector<ContextObject*>& ContextObject::GetDependencies() const noexcept
{
    return m_dependencies;
}

void ContextObject::AddTopLevelDependency(ContextObject* obj)
{
    if(obj != nullptr)
        m_top_level_dependencies.push_back(obj);
}

bool ContextObject::HasTopLevelDependency() const noexcept
{
    return !m_top_level_dependencies.empty();
}
