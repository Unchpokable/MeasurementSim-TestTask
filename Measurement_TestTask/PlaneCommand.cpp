#include "PlaneCommand.h"
#include "PointCommand.h"

void PlaneCommand::Execute(const std::vector<ContextObject*>& args)
{
    m_base_points.clear();
    m_base_points_data.clear();

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
    Emit(this);
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
    return PlaneFromPoints(pt1, pt2, pt3);
}

QString PlaneCommand::ToString()
{
    if(m_base_points.size() != 3)
        return { "Invalid object" };

    std::stringstream out {};

    out << "$PLANE(ID::" << GetName().toStdString() << ", " << m_base_points[0]->GetName().toStdString()
        << ", " << m_base_points[1]->GetName().toStdString()
        << ", " << m_base_points[1]->GetName().toStdString() << ")\n";

    return QString::fromUtf8(out.str());
}

QString PlaneCommand::ToPrettyString()
{
    if(m_base_points.size() != 3)
        return "Invalid object";

    QString out {};
    out.append("Plane object\n");
    out.append("based on: " + dynamic_cast<CommandBase*>(m_base_points[0])->ToPrettyString() + "\n");
    out.append(dynamic_cast<CommandBase*>(m_base_points[0])->ToPrettyString() + "\n");
    out.append(dynamic_cast<CommandBase*>(m_base_points[0])->ToPrettyString() + "\n");

    out.append("Nominal: " + Plane3dToString(m_nominal_plane_params));
    out.append("Actual: " + Plane3dToString(m_plane_params) + "\n\n");

    return out;
}

