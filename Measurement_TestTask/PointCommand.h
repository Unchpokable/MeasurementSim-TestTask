#pragma once

#include "eigen/include/Eigen/Core"

#include "ContextObject.h"
#include "CommandBase.h"
#include "RuntimeContext.h"
#include "Formats.h"
#include "GeometryData.h"
#include "type_traits";

using Point3d = Eigen::Vector3d;

class PointCommand : public CommandBase, public ContextObject
{
public:
    PointCommand(RuntimeContext* context, const QString& obj_name)
    {
        m_context = context;
        m_object_name = obj_name;
        SetType(ci_point);
    }

    ~PointCommand() override = default;
    void Execute(const std::vector<double>& args) override;
    QString ToString() override;
    Data3D GetDimensionalInfo() const noexcept;

private:
    void Init(const Point3d& initial_pos, const Eigen::Vector3d& normal);

    std::string NominalToString(Brackets brackets);
    std::string ActualToString(Brackets brackets);
    std::string NormalToString(Brackets brackets);

    Point3d m_nominal_position;
    Point3d m_actual_position;
    Eigen::Vector3d m_normal;

    RuntimeContext* m_context;
};

