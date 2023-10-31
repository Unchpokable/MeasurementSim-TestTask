#pragma once
#include <QString>

enum ContextObjectType {
    ci_comment,
    ci_move,
    ci_point,
    ci_plane,
    ci_circle,
    ci_circle_to_point,
    ci_project,
    ci_point_diff,
    ci_circle_diff
};

class ContextObject
{
public:
    ContextObject() : m_object_name("")
    {
    }

    ContextObject(QString name) : m_object_name(std::move(name))
    {
    }

    ContextObject(const ContextObject& other) = default;

    ContextObject(ContextObject&& other) noexcept : m_object_name(std::move(other.m_object_name))
    {
    }

    ContextObject& operator=(const ContextObject& other)
    {
        if(this != &other) 
        {
            m_object_name = other.m_object_name;
        }
        return *this;
    }

    ContextObject& operator=(ContextObject&& other) noexcept
    {
        if(this != &other) 
        {
            m_object_name = std::move(other.m_object_name);
        }
        return *this;
    }

    virtual ~ContextObject() = default;

    virtual bool IsEquals(const ContextObject& other);
    QString Name();

protected:
    QString m_object_name;
};
