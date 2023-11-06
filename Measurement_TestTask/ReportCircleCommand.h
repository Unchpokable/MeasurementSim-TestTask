#pragma once
#include "CircleCommand.h"
#include "CommandBase.h"
class ReportCircleCommand : public CommandBase, public ContextObject
{
public:
    ReportCircleCommand(const QString& obj_name, double max_center_diff, double max_radius_diff) : ContextObject(obj_name, ci_circle_diff)
    {
        m_max_center_diff = max_center_diff;
        m_max_radius_diff = max_radius_diff;
    }

    void Execute(const std::vector<ContextObject*>& args) override;
    QString ToString() override;
    bool IsSatisfyingCondition() const noexcept;

private:
    CircleCommand* m_root;

    double m_max_center_diff;
    double m_max_radius_diff;

    double m_measured_center_diff;
    double m_measured_radius_diff;
};

