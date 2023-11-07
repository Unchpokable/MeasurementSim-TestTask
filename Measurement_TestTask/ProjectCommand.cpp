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

    m_result_point->m_actual_position = projection_actual;
    m_result_point->m_nominal_position = projection_nominal;
    m_result_point->m_normal = plane->GetActualPlane().Normal;

    Emit(this);
}

QString ProjectCommand::ToString()
{
    QString out {};
    out.append("$PROJECT(ID::" + m_display_name + ", ");
    out.append(m_root->GetName() + ", ");
    out.append(m_plane->GetName() + ")");
    return out; // $PROJECT(ID::PRJ1, PT1, PL1)
}

QString ProjectCommand::ToPrettyString()
{
    QString out {};

    out.append("Projected point\n");
    out.append("Base point: " + m_root->ToPrettyString() + "\n");
    out.append("Projection plane: " + m_plane->ToPrettyString() + "\n");
    out.append("Projected point:\n" + m_result_point->ToPrettyString() + "\n");

    return out;
}
