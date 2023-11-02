#pragma once
#include <vector>

#include "ContextObject.h"
#include "MeasureMachine.h"

class RuntimeContext;

using ContextOperationCallback = void(RuntimeContext*, QString);

class RuntimeContext
{
public:
    RuntimeContext() : RuntimeContext(Eigen::Vector3d(0,0,0))
    {
        m_context_objects = new std::vector<ContextObject*>();
    }

    RuntimeContext(const RuntimeContext& other) : RuntimeContext(Eigen::Vector3d(0, 0, 0))
    {
        m_context_objects = new std::vector(*(other.m_context_objects));
    }

    RuntimeContext(RuntimeContext&& other) noexcept
    {
        m_context_objects = new std::vector(*other.m_context_objects);
        other.m_context_objects = nullptr;

        m_measure_machine = new MeasureMachine(*other.m_measure_machine);
        delete other.m_measure_machine;
    }

    ~RuntimeContext();

    RuntimeContext& operator=(const RuntimeContext& other)
    {
        if(this != &other)
        {
            delete m_context_objects;
            m_context_objects = new std::vector(*other.m_context_objects);
        }
        return *this;
    }

    RuntimeContext& operator=(RuntimeContext&& other) noexcept
    {
        if(this != &other)
        {
            delete m_context_objects;
            m_context_objects = other.m_context_objects;
            other.m_context_objects = nullptr;
        }
        return *this;
    }


    bool RemoveObject(const QString& object_name, ContextOperationCallback callback = nullptr);
    bool AddObject(ContextObject* object, ContextOperationCallback callback = nullptr);
    const ContextObject* GetObjectByName(const QString& object_name) const noexcept;
    const std::vector<ContextObject*>* GetContextObjects() const noexcept;
    const MeasureMachine* GetMeasureMachine() const noexcept;
    const std::vector<ContextObject*>& FindDependencies(const QString& object_name);


private:
    RuntimeContext(const Eigen::Vector3d& machine_initial_position)
    {
        m_measure_machine = new MeasureMachine(machine_initial_position);
    }

    std::vector<ContextObject*>* m_context_objects;
    MeasureMachine* m_measure_machine;
};
