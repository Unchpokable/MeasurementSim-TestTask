#pragma once

#include "eigen/include/Eigen/Core"

#include "ContextObject.h"
#include "CommandBase.h"
#include "RuntimeContext.h"
#include "Formats.h"
#include "GeometryData.h"

using Point3d = Eigen::Vector3d;

class PointCommand : public CommandBase, public ContextObject
{
    friend class CircleCenterCommand;
    friend class ProjectCommand;

public:
    PointCommand(RuntimeContext* context, const QString& obj_name) : ContextObject(obj_name, ci_point)
    {
        m_context = context;
    }

    ~PointCommand() override = default;
    void Execute(const std::vector<double>& args) override;
    QString ToString() override;
    QString ToPrettyString() override;
    Data3D GetDimensionalInfo() const noexcept;

private:
    void Init(const Point3d& initial_pos, const Eigen::Vector3d& normal);
    bool Register();

    std::string NominalToString(Brackets brackets);
    std::string ActualToString(Brackets brackets);
    std::string NormalToString(Brackets brackets);

    Point3d m_nominal_position;
    Point3d m_actual_position;
    Eigen::Vector3d m_normal;

    RuntimeContext* m_context;
};

