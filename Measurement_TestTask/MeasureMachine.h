#pragma once

#include "eigen/include/Eigen/Core"

using Point3d = Eigen::Vector3d;

class MeasureMachine
{
public:
    MeasureMachine()
        : m_touch_probe_position(0,0,0)
    {
    }

    MeasureMachine(double x, double y, double z)
        : m_touch_probe_position(x, y, z)
    {
    }

    MeasureMachine(const Point3d& position)
        : m_touch_probe_position(position)
    {
    }

    MeasureMachine(const Point3d&& rvPosition)
        : m_touch_probe_position(rvPosition)
    {
    }

    MeasureMachine(MeasureMachine& origin) noexcept
    {
        m_touch_probe_position = std::move(origin.m_touch_probe_position);
    }

    void Move(const Eigen::Vector3d& direction);
    void SetPosition(const Point3d& where);
    void Zero();

    Point3d GetPoint(const Eigen::Vector3d& normal, const Point3d& nominal_value);
    Point3d GetProbePosition() const noexcept;


private:
    Eigen::Vector3d m_touch_probe_position;
    double m_minimal_step_size = 1e-6; // 0.000001
};

