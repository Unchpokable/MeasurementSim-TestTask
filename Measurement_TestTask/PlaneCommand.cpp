#include "PlaneCommand.h"
#include "PointCommand.h"

void PlaneCommand::Execute(const std::vector<ContextObject*>& args)
{
    for (const auto arg: args)
    {
        auto point = dynamic_cast<PointCommand*>(arg);
        if(point == nullptr)
            throw std::invalid_argument("PlaneCommand received inconsistent type of one of its arguments - can not be casted to PointCommand");

        auto data = point->GetDimensionalInfo();
        m_base_points.push_back(point);
        m_base_points_data.push_back(data);
    }

    if(m_base_points.size() != 3)
        throw std::invalid_argument("Plane should be built based on 3 points");

    CalculateActual(m_base_points_data[0].ActualPosition, m_base_points_data[1].ActualPosition, m_base_points_data[2].ActualPosition);
    CalculateNominal(m_base_points_data[0].NominalPosition, m_base_points_data[1].NominalPosition, m_base_points_data[2].NominalPosition);
}

void PlaneCommand::CalculateActual(const Point3d& pt1, const Point3d& pt2, const Point3d& pt3)
{
    m_plane_params = CalculatePlane(pt1, pt2, pt3);
}

void PlaneCommand::CalculateNominal(const Point3d& pt1, const Point3d& pt2, const Point3d& pt3)
{
    m_nominal_plane_params = CalculatePlane(pt1, pt2, pt3);
}

Plane3d PlaneCommand::CalculatePlane(const Point3d& pt1, const Point3d& pt2, const Point3d& pt3)
{
    auto v1 = pt2 - pt1;
    auto v2 = pt3 - pt1;

    auto normal = v1.cross(v2).normalized();

    auto a = normal.x();
    auto b = normal.y();
    auto c = normal.z();
    auto d = -a * pt1.x() - b * pt1.y() - c * pt1.z();

    return Plane3d { a, b, c, d, normal };
}

QString PlaneCommand::ToString()
{
    if(m_base_points.size() != 3)
        return { "Invalid object" };

    std::stringstream out {};

    out << "$PLANE(ID::" << GetName().toStdString() << ", " << m_base_points[0]->GetName().toStdString()
        << ", " << m_base_points[1]->GetName().toStdString()
        << ", " << m_base_points[1]->GetName().toStdString() << ")";

    return QString::fromUtf8(out.str());
}

