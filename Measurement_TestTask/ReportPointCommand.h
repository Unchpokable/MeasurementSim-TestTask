#pragma once
#include "CommandBase.h"
#include "PointCommand.h"

class ReportPointCommand : public CommandBase, public ContextObject
{
public:
    ReportPointCommand(QString name, double max_diff)
        : ContextObject(name, ci_point_diff)
    {
        m_maximum_diff = max_diff;
    }

    void Execute(const std::vector<ContextObject*>& args) override;
    QString ToString() override;
    bool IsSatisfyingCondition() const noexcept;

private:
    PointCommand* m_root;
    double m_maximum_diff;
    double m_measured_diff;
};

