#pragma once
#include "eigen/include/Eigen/Core"
#include "eigen/include/Eigen/Dense"
#include "CommandBase.h"
#include "GeometryData.h"

using Point3d = Eigen::Vector3d;

struct Plane3d
{
    double A, B, C, D;
    Eigen::Vector3d Normal;
};

class PlaneCommand : public CommandBase , public ContextObject
{
public:
    PlaneCommand()
    {
        m_nominal_plane_params = Plane3d();
        m_plane_params = m_nominal_plane_params;
        SetType(ci_plane);
    }

    void Init();

    void Execute(const std::vector<ContextObject*>& args) override;
    QString ToString() override;

private:
    void CalculateActual(const Point3d& pt1, const Point3d& pt2, const Point3d& pt3);
    void CalculateNominal(const Point3d& pt1, const Point3d& pt2, const Point3d& pt3);
    static Plane3d CalculatePlane(const Point3d& pt1, const Point3d& pt2, const Point3d& pt3);
    Point3d m_nominal_coordinates;
    Point3d m_actual_coordinates;
    Plane3d m_plane_params;
    Plane3d m_nominal_plane_params;
    std::vector<Data3D> m_base_points_data;
    std::vector<ContextObject*> m_base_points;
};

