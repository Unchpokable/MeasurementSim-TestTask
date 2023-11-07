#include "ReportPointCommand.h"

#include <iomanip>
#include <stdexcept>

#include "PointCommand.h"

void ReportPointCommand::Execute(const std::vector<ContextObject*>& args)
{
    if(args.size() != 1)
        throw std::invalid_argument("Report command should take an only one object argument - Point");

    const auto point = dynamic_cast<PointCommand*>(args[0]);
    if(point == nullptr)
        throw std::invalid_argument("Given object is not a point");
    m_root = point;

    const auto point_data = point->GetDimensionalInfo();

    const auto diff = point_data.ActualPosition - point_data.NominalPosition;
    m_measured_diff = diff.norm();

    Emit(this);
}

QString ReportPointCommand::ToString()
{
    QString out {};

    out.append("$REPORT_PT(" + m_root->GetName() + ", ");
    out.append((std::stringstream{} << std::fixed << std::setprecision(3) << m_measured_diff).str());
    out.append(")");

    return out;
}

bool ReportPointCommand::IsSatisfyingCondition() const noexcept
{
    return m_measured_diff < m_maximum_diff;
}

QString ReportPointCommand::ToPrettyString()
{
    QString out {};

    const auto check_msg = IsSatisfyingCondition() ? "\nPoint check\n" : "\nPoint fail\n";

    out.append(check_msg);
    out.append("Difference: " + (std::stringstream {} << std::fixed << std::setprecision(3)
        << m_measured_diff).str() + "\n");

    return out;
}
