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

bool RuntimeContext::RemoveObject(const QString& object_name, const ContextOperationCallback& callback)
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
        if (callback != nullptr)
            callback(this, QString("Unable to remove object named " + object_name + ", because there is no object called that"));
        return false;
    }

    return true;
}

bool RuntimeContext::AddObject(ContextObject* object, const ContextOperationCallback& callback)
{
    if (object == nullptr)
    {
        if (callback != nullptr)
            callback(this, QString("Unable to add nullptr value to context"));
        return false;
    }

    if (std::find(m_context_objects->begin(), m_context_objects->end(), object) != m_context_objects->end() ||
        std::find_if(m_context_objects->begin(), m_context_objects->end(), 
        [object](ContextObject* ctx)
        {
                return ctx->GetName() == object->GetName();
        }) != m_context_objects->end())
    {
        if (callback != nullptr)
            callback(this, QString("Unable to add object named " + object->GetName() + ", because this object already added to context or this object has the same name with other different object"));
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

std::shared_ptr<std::vector<ContextObject*>> RuntimeContext::GetObjectsOfType(ContextObjectType type) const noexcept
{
    auto out = std::make_shared<std::vector<ContextObject*>>();

    for (const auto obj: *m_context_objects)
    {
        if(obj->GetType() == type)
            out->push_back(obj);
    }

    return out;
}


const std::vector<ContextObject*>* RuntimeContext::GetContextObjects() const noexcept
{
    return m_context_objects;
}

const MeasureMachine* RuntimeContext::GetMeasureMachine() const noexcept
{
    return m_measure_machine;
}

std::shared_ptr<std::vector<ContextObject*>> RuntimeContext::GetObjectDependencies(const QString& object_name) const noexcept
{
    auto out = std::make_shared<std::vector<ContextObject*>>(); // slow but quite safety

    const auto obj = GetObjectByName(object_name);

    for (auto dep: obj->GetDependencies())
    {
        out->push_back(dep);
    }

    return out;
}

// Returns bool flag that allow or does not allow to make some ContextObjects dependent to some root object.
// Dependent objects should be placed in context vector left from root
bool RuntimeContext::BindDependencies(ContextObject* root, const std::vector<ContextObject*>& deps) const noexcept
{
    auto root_iter_pos = std::find(m_context_objects->begin(), m_context_objects->end(), root);

    if(root_iter_pos == m_context_objects->end())
        return false;

    for(auto dep_it { deps.begin() }; dep_it != deps.end(); dep_it++)
    {
        if(std::find(m_context_objects->begin(), m_context_objects->end(), *dep_it) >= root_iter_pos)
            return false;
        root->AddDependentObject(*dep_it);
    }
    return true;
}

