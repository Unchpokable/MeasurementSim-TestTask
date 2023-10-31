#pragma once

#include "eigen/include/Eigen/Core"

#include "ContextObject.h"
#include "CommandBase.h"
#include "RuntimeContext.h"
#include "Formats.h"

using Point3d = Eigen::Vector3d;

class PointCommand : public CommandBase, public ContextObject
{
public:
    PointCommand(RuntimeContext* context)
    {
        m_context = context;
        SetType(ci_point);
    }

    ~PointCommand() override = default;

    void Init(const Point3d& initial_pos, const Eigen::Vector3d& normal);
    void Execute(const std::vector<double>& args) override;
    QString ToString() override;

private:

    std::string NominalToString(Brackets brackets);
    std::string ActualToString(Brackets brackets);
    std::string NormalToString(Brackets brackets);

    Point3d m_nominal_position;
    Point3d m_actual_position;
    Eigen::Vector3d m_normal;

    RuntimeContext* m_context;
};

