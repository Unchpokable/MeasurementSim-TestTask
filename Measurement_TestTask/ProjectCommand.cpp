#include "ProjectCommand.h"

void ProjectCommand::Execute(const std::vector<ContextObject*>& args)
{
    if(args.size() != 2)
        throw std::invalid_argument("Point projection can be built only based on single one point and to one single plane");

    const auto point = dynamic_cast<PointCommand*>(args[0]);
    const auto plane = dynamic_cast<PlaneCommand*>(args[1]);

    if(point == nullptr)
        throw std::invalid_argument("Wrong parameter given: source point");
    if(plane == nullptr)
        throw std::invalid_argument("Wrong argument given: source plane");

    m_root = point;
    m_plane = plane;

    const auto projection_nominal = Project(point->GetDimensionalInfo().ActualPosition,
        plane->GetNominalPlane());

    const auto projection_actual = Project(point->GetDimensionalInfo().NominalPosition,
        plane->GetActualPlane());

    m_projection = { projection_actual, projection_nominal,
        plane->GetActualPlane().Normal, plane->GetNominalPlane().Normal
    };
}

QString ProjectCommand::ToString()
{
    QString out {};
    out.append("$PROJECT(ID::" + GetName() + ", ");
    out.append(m_root->GetName() + ", ");
    out.append(m_plane->GetName() + ")");
    return out; // $PROJECT(ID::PRJ1, PT1, PL1)
}

const ProjectionPoint3d& ProjectCommand::GetProjectedPoint()
{
    return m_projection;
}
