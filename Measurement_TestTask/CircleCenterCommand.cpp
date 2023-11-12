#include "CircleCenterCommand.h"
#include "Formats.h"
#include "CircleCommand.h"

void CircleCenterCommand::Execute(const std::vector<ContextObject*>& args)
{
    if(args.size() != 1)
        throw std::invalid_argument("Can not get center point of multiple circles at one time");

    const auto circle = dynamic_cast<CircleCommand*>(args[0]);

    m_root = circle;
    const auto actual = circle->GetActualCircle();
    const auto nominal = circle->GetNominalCircle();

    m_data.ActualPosition = actual.CenterPoint;
    m_data.ActualNormal = actual.Normal;

    m_data.NominalPosition = nominal.CenterPoint;
    m_data.Normal = nominal.Normal;

    m_result_point->m_actual_position = m_data.ActualPosition;
    m_result_point->m_nominal_position = m_data.NominalPosition;
    m_result_point->m_normal = m_data.Normal;

    Emit(this);
}

QString CircleCenterCommand::ToString()
{
    QString out {};
    out.append("$CIRCLE_CENTER(ID::" + m_display_name + ", ");
    out.append(m_root->GetName() + ")");
    return out;
}

QString CircleCenterCommand::ToPrettyString()
{
    QString out {};

    out.append("Center of Circle " + m_root->GetName() + " with ID=" + GetName() 
        + " at\n" + Data3d2String(m_data, false) + "\n\n");
    return out;
}


const Data3D& CircleCenterCommand::GetDimensionalData()
{
    return m_data;
}

const PointCommand* CircleCenterCommand::GetGeneratedPoint() const noexcept
{
    return m_result_point;
}