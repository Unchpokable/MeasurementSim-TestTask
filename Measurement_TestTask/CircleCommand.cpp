#include "CircleCommand.h"
#include "PointCommand.h"

void CircleCommand::Execute(const std::vector<ContextObject*>& args)
{
    m_base_points.clear();
    m_base_points_data.clear();

    for (const auto arg: args)
    {
        const auto point = dynamic_cast<PointCommand*>(arg);
        if(point == nullptr)
            throw std::invalid_argument("Given object is not a point");

        auto data = point->GetDimensionalInfo();

        m_base_points_data.push_back(data);
        m_base_points.push_back(point);
    }

    if(m_base_points_data.size() != 3)
        throw std::invalid_argument("Circle can be built only based on 3 points");

    CalculateNominal();
    CalculateActual();

    Emit(this);
}

void CircleCommand::CalculateActual()
{
    m_actual_circle = CircleFromPoints(m_base_points_data[0].ActualPosition,
        m_base_points_data[1].ActualPosition,
        m_base_points_data[2].ActualPosition);
}

void CircleCommand::CalculateNominal()
{
    m_actual_circle = CircleFromPoints(m_base_points_data[0].NominalPosition,
        m_base_points_data[1].NominalPosition,
        m_base_points_data[2].NominalPosition);
}

QString CircleCommand::ToString()
{
    if(m_base_points.size() != 3)
        return QString("Invalid object");

    QString out {};
    out.append("$CIRCLE(ID::" + GetName().toStdString() + " ");
    out.append(m_base_points[0]->GetName().toStdString() + " ");
    out.append(m_base_points[1]->GetName().toStdString() + " ");
    out.append(m_base_points[2]->GetName().toStdString() + ")\n");

    return out;
}

QString CircleCommand::ToPrettyString()
{
    if(m_base_points.size() != 3)
        return QString("Invalid object");

    QString out {};
    out.append("Circle based on: " + dynamic_cast<CommandBase*>(m_base_points[0])->ToPrettyString() + "\n");
    out.append(dynamic_cast<CommandBase*>(m_base_points[0])->ToPrettyString() + "\n");
    out.append(dynamic_cast<CommandBase*>(m_base_points[0])->ToPrettyString() + "\n");

    out.append("Nominal: " + Circle3d2String(m_nominal_circle)+ "\n" );
    out.append("Actual: " + Circle3d2String(m_actual_circle) + "\n\n");

    return out;
}


const Circle3d& CircleCommand::GetNominalCircle()
{
    return m_nominal_circle;
}

const Circle3d& CircleCommand::GetActualCircle()
{
    return m_actual_circle;
}

