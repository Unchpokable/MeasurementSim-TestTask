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

bool RuntimeContext::RemoveObject(const QString& object_name) noexcept
{
    
    const auto where = std::find_if(m_context_objects->begin(),
        m_context_objects->end(),
        [object_name](ContextObject* ctx) {
        return ctx->GetName() == object_name;
    });

    if(where != m_context_objects->end())
    {
        m_context_objects->erase(where);
        return true;
    }

    return false;
}

bool RuntimeContext::RemoveObject(std::size_t position) noexcept
{
    if(position < 0 || position >= m_context_objects->size())
        return false;

    const auto it = m_context_objects->begin();
    const auto pos = it + position;

    if(pos >= m_context_objects->end()) 
        return false;

    m_context_objects->erase(it + position);
    return true;
}


bool RuntimeContext::AddObject(ContextObject* object) noexcept
{
    if (object == nullptr)
    {
        return false;
    }

    if (std::find(m_context_objects->begin(), m_context_objects->end(), object) != m_context_objects->end() ||
        std::find_if(m_context_objects->begin(), m_context_objects->end(), 
        [object](ContextObject* ctx)
        {
                return ctx->GetName() == object->GetName();
        }) != m_context_objects->end())
    {
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

ContextObject* RuntimeContext::GetObjectByIndex(std::size_t index) const noexcept
{
    if(index < 0 || m_context_objects->size() <= index)
        return nullptr;

    return (*m_context_objects)[index];
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

    std::vector<ContextObject*> allowed_dependencies {};

    for(auto dep_it : deps)
    {
        if(std::find(m_context_objects->begin(), m_context_objects->end(), dep_it) >= root_iter_pos)
            return false;
        allowed_dependencies.push_back(dep_it);
    }

    if (allowed_dependencies.size() == deps.size())
    {
        for(const auto dep : allowed_dependencies)
            root->AddDependentObject(dep);
    }

    return true;
}

bool RuntimeContext::ReplaceObject(std::size_t position, ContextObject* new_object) noexcept
{
    if(position < 0 || position >= m_context_objects->size())
        return false;

    if(new_object == nullptr)
        return false;

    m_context_objects->at(position) = new_object;
    return true;
}

bool RuntimeContext::InsertObject(std::size_t position, ContextObject* new_object) noexcept
{
    if(position < 0 || position >= m_context_objects->size())
        return false;

    if(new_object == nullptr)
        return false;

    const auto it = m_context_objects->begin();
    m_context_objects->insert(it + position, new_object);
    return true;
}


