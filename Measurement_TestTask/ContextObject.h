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
    ci_circle_diff,

    ci_undefined
};

class ContextObject
{
public:
    ContextObject() : m_object_name(""), m_type(ci_undefined)
    {
    }

    ContextObject(QString name) : m_object_name(std::move(name)), m_type(ci_undefined)
    {
    }

    ContextObject(const ContextObject& other) = default;

    ContextObject(ContextObject&& other) noexcept : m_object_name(std::move(other.m_object_name)),
                                                    m_type(other.m_type)
    {
    }

    ContextObject& operator=(const ContextObject& other)
    {
        if(this != &other) 
        {
            m_object_name = other.m_object_name;
            m_type = other.m_type;
        }
        return *this;
    }

    ContextObject& operator=(ContextObject&& other) noexcept
    {
        if(this != &other) 
        {
            m_object_name = std::move(other.m_object_name);
            m_type = other.m_type;
        }
        return *this;
    }

    virtual ~ContextObject() = default;

    virtual bool IsEquals(const ContextObject& other) const noexcept;
    QString GetName() const noexcept;
    ContextObjectType GetType() const noexcept;

protected:
    QString m_object_name;
    ContextObjectType m_type;
};
