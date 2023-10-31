#include "RuntimeContext.h"
#include <algorithm>


template<typename T, typename UnaryPredicate>
std::vector<T>* exclude_if(std::vector<T>* vec, UnaryPredicate predicate, int* skipped)
{
    if(skipped == nullptr)
        throw std::exception("null pointer argument");

    *skipped = 0;

    auto result = new std::vector<T>;
    
    for (T it: *vec)
    {
        if(predicate(it))
            (*skipped)++;
        else
            result->push_back(it);
    }

    return result;
}

RuntimeContext::~RuntimeContext() {
    for(const auto obj : *m_context_objects)
        delete obj;
    delete m_context_objects;
}

bool RuntimeContext::RemoveObject(const QString& object_name, ContextOperationCallback callback)
{
    auto ref_count = 0;

    auto others = exclude_if(m_context_objects,
                                        [object_name](ContextObject* ctx) {
        return ctx->GetName() == object_name;
    }, &ref_count);

    if(ref_count == 0)
    {
        const auto where = std::find_if(m_context_objects->begin(),
            m_context_objects->end(),
            [object_name](ContextObject* ctx) {
            return ctx->GetName() == object_name;
        });

        if(where != m_context_objects->end())
            m_context_objects->erase(where);

        else
        {
            callback(this, QString("Unable to remove object named " + object_name + ", because there is no object called that"));
            return false;
        }

        return true;
    }
    if (callback != nullptr)
        callback(this, QString("Unable to remove object " + object_name + ", because other objects depends on it"));
    return false;
}

bool RuntimeContext::AddObject(ContextObject* object, ContextOperationCallback callback)
{
    if (object == nullptr)
    {
        callback(this, QString("Unable to add nullptr value to context"));
        return false;
    }

    if (std::find(m_context_objects->begin(), m_context_objects->end(), object) != m_context_objects->end())
    {
        callback(this, QString("Unable to add object named " + object->GetName() + ", because there is already object named that"));
        return false;
    }

    m_context_objects->push_back(object);
    return true;
}

const ContextObject* RuntimeContext::GetObjectByName(const QString& object_name) const noexcept
{
    auto obj = std::find_if(m_context_objects->begin(), m_context_objects->end(),
        [object_name](ContextObject* ctx) {
        return ctx->GetName() == object_name;
    });

    if(obj != m_context_objects->end())
        return *obj;
    return nullptr;
}

const std::vector<ContextObject*>* RuntimeContext::GetContextObjects() const noexcept
{
    return m_context_objects;
}

const MeasureMachine* RuntimeContext::GetMeasureMachine() const noexcept
{
    return m_measure_machine;
}

