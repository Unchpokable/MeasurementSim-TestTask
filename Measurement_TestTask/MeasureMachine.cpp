#include "MeasureMachine.h"

#include <random>

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
Point3d MeasureMachine::GetPoint(const Eigen::Vector3d& normal, const Point3d& nominal_value) const noexcept
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1, 1);

    const double offset_x = dis(gen) * m_random_point_radius;
    const double offset_y = dis(gen) * m_random_point_radius;
    const double offset_z = dis(gen) * m_random_point_radius;

    return nominal_value + (Eigen::Vector3d(offset_x, offset_y, offset_z));
}

