#include "ReportCircleCommand.h"

#include <iomanip>

QString DoubleToString(double val)
{
    return QString::fromUtf8((std::stringstream {} << std::fixed << std::setprecision(3) << val).str());
}

void ReportCircleCommand::Execute(const std::vector<ContextObject*>& args)
{
    if(args.size() != 1)
        throw std::invalid_argument("Report command should take an only one object argument - Point");

    const auto circle = dynamic_cast<CircleCommand*>(args[0]);
    if(circle == nullptr)
        throw std::invalid_argument("Given object is not a point");
    m_root = circle;

    const auto n_circle = m_root->GetNominalCircle();
    const auto act_circle = m_root->GetActualCircle();

    m_measured_center_diff = (n_circle.CenterPoint - act_circle.CenterPoint).norm();
    m_measured_radius_diff = n_circle.Radius - act_circle.Radius;
}

QString ReportCircleCommand::ToString()
{
    QString out {};
    out.append("$REPORT_PLANE(" + m_root->GetName() + ", " 
        + DoubleToString(m_max_center_diff) + ", " 
        + DoubleToString(m_max_radius_diff));
    return out;
}

bool ReportCircleCommand::IsSatisfyingCondition() const noexcept
{
    return (m_measured_center_diff < m_max_center_diff) && (m_measured_radius_diff < m_max_radius_diff);
}
