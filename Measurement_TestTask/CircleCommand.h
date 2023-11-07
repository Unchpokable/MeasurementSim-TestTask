#pragma once
#include "CommandBase.h"
#include "GeometryData.h"
#include "MathFunctions.h"

class CircleCommand : public CommandBase, public ContextObject
{
public:
    CircleCommand(const QString& obj_name) : ContextObject(obj_name, ci_circle)
    {
        m_actual_circle = {};
        m_nominal_circle = {};
    }

    void Execute(const std::vector<ContextObject*>& args) override;
    QString ToString() override;
    QString ToPrettyString() override;

    const Circle3d& GetNominalCircle();
    const Circle3d& GetActualCircle();
private:

    void CalculateActual();
    void CalculateNominal();

    Circle3d m_nominal_circle;
    Circle3d m_actual_circle;

    std::vector<Data3D> m_base_points_data;
    std::vector<ContextObject*> m_base_points;
};

