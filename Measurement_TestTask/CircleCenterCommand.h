#pragma once
#include "CircleCommand.h"
#include "CommandBase.h"
#include "GeometryData.h"
#include "MathFunctions.h"

class CircleCenterCommand : public CommandBase, public ContextObject
{
public:
    CircleCenterCommand(const QString& obj_name) : ContextObject(obj_name, ci_circle_to_point)
    {
    }
    void Execute(const std::vector<ContextObject*>& args) override;
    QString ToString() override;

    const Data3D& GetDimensionalData();

private:
    Data3D m_data;
    const CircleCommand* m_root; // will be sets in Execute
};

