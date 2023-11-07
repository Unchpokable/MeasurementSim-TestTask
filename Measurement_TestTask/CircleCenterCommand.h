#pragma once
#include <iomanip>

#include "CircleCommand.h"
#include "CommandBase.h"
#include "GeometryData.h"
#include "MathFunctions.h"
#include "PointCommand.h"
#include "Formats.h"

class CircleCenterCommand : public CommandBase, public ContextObject
{
public:
    CircleCenterCommand(const QString& obj_name, PointCommand* result_point) :
        ContextObject(QString(obj_name) + "_autogen_<" + RandomString(5) + ">",
            ci_circle_to_point),

        m_display_name(obj_name)
    {
        m_result_point = result_point;
    }

    void Execute(const std::vector<ContextObject*>& args) override;
    QString ToString() override;
    QString ToPrettyString() override;

    const Data3D& GetDimensionalData();
    const PointCommand* GetGeneratedPoint() const noexcept;

private:
    Data3D m_data;
    const CircleCommand* m_root; // will be sets in Execute

    QString m_display_name;
    PointCommand* m_result_point;
};

