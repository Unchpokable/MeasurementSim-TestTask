#pragma once
#include "eigen/include/Eigen/Core"
#include "eigen/include/Eigen/Dense"
#include "CommandBase.h"
#include "GeometryData.h"
#include "MathFunctions.h"

class PlaneCommand : public CommandBase , public ContextObject
{
public:
    PlaneCommand(const QString& obj_name)
    {
        m_nominal_plane_params = Plane3d();
        m_plane_params = m_nominal_plane_params;
        SetType(ci_plane);
        m_object_name = obj_name;
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

