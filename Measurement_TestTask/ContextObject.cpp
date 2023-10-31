#include "ContextObject.h"

bool ContextObject::IsEquals(const ContextObject& other)
{
    return m_object_name == other.m_object_name;
}


QString ContextObject::Name()
{
    return m_object_name;
}

