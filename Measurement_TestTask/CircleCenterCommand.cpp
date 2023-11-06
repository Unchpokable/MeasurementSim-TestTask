#include "CircleCenterCommand.h"

#include "CircleCommand.h"

void CircleCenterCommand::Execute(const std::vector<ContextObject*>& args)
{
    if(args.size() != 1)
        throw std::invalid_argument("Can not gen center point of multiple circles at one time");

    const auto circle = dynamic_cast<CircleCommand*>(args[0]);
    m_root = circle;
    const auto actual = circle->GetActualCircle();
    const auto nominal = circle->GetNominalCircle();

    m_data.ActualPosition = actual.CenterPoint;
    m_data.ActualNormal = actual.Normal;

    m_data.NominalPosition = nominal.CenterPoint;
    m_data.Normal = nominal.Normal;
}

QString CircleCenterCommand::ToString()
{
    QString out {};
    out.append("$CIRCLE_CENTER(ID::" + GetName() + ", ");
    out.append(m_root->GetName() + ")");
    return out;
}

const Data3D& CircleCenterCommand::GetDimensionalData()
{
    return m_data;
}

