#include "MeasureMachine.h"

void MeasureMachine::Move(const Eigen::Vector3d& direction)
{
    m_touch_probe_position += direction;
}

void MeasureMachine::SetPosition(const Eigen::Vector3d& where)
{
    m_touch_probe_position = where;
}

void MeasureMachine::Zero()
{
    m_touch_probe_position.setZero();
}

Point3d MeasureMachine::GetProbePosition() const noexcept
{
    return m_touch_probe_position;
}

// Emulates point measurement. Actually, generate value that differs with nominal quite little
Point3d MeasureMachine::GetPoint(const Eigen::Vector3d& normal, const Point3d& nominal_value)
{
    const auto n = normal.normalized();
    const auto virtual_distance = rand() % 1000;
    const auto move = m_minimal_step_size * virtual_distance;

    const auto distance_to_probe = m_touch_probe_position - nominal_value;

    Move(distance_to_probe);

    return nominal_value + (n * move); // Kinda little move in normal directoin
}

