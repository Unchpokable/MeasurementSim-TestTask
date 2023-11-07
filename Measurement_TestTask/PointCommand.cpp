#include "PointCommand.h"
#include "Formats.h"
#include "DefaultCallbacks.h"

void PointCommand::Init(const Point3d& initial_pos, const Eigen::Vector3d& normal)
{
    m_nominal_position = initial_pos;
    m_normal = normal;
    m_actual_position = m_nominal_position;
}

void PointCommand::Execute(const std::vector<double>& args)
{
    if(args.size() != 6)
        throw std::invalid_argument("Not enough parameters for point command");

    const Point3d nominal_pos(args[0], args[1], args[2]);
    const Eigen::Vector3d normal(args[3], args[4], args[5]);

    Init(nominal_pos, normal);

    const auto machine = m_context->GetMeasureMachine();
    m_actual_position = const_cast<MeasureMachine*>(machine)->GetPoint(m_normal, m_nominal_position);
    Emit(this);
}

QString PointCommand::ToString() {
    std::stringstream out {};

    out << "$POINT(";
    out << "ID::" << m_object_name.toStdString() << ", ";
    out << "CRD::" << NominalToString(BR_ROUND) << ", ";
    out << "NORM::" << NormalToString(BR_ROUND) << ")\n";

    return QString::fromUtf8(out.str().c_str());
}

QString PointCommand::ToPrettyString()
{
    QString out;

    out.append("Point\nNominal:" + Point2String(m_nominal_position));
    out.append("\nActual: " + Point2String(m_actual_position));

    return out;
}


Data3D PointCommand::GetDimensionalInfo() const noexcept
{
    Data3D out{};
    out.ActualPosition = m_actual_position;
    out.NominalPosition = m_nominal_position;
    out.Normal = m_normal;
    out.ActualNormal = out.Normal;
    return out;
}


std::string PointCommand::NominalToString(Brackets brackets)
{
    auto bracket = GetBracket(brackets);
    std::stringstream out {};
    out << bracket.Open << m_nominal_position.x() << ", " << m_nominal_position.y() << ", " << m_nominal_position.z() << bracket.Close;
    return out.str();
}

std::string PointCommand::ActualToString(Brackets brackets)
{
    auto bracket = GetBracket(brackets);
    std::stringstream out {};
    out << bracket.Open << m_actual_position.x() << ", " << m_actual_position.y() << ", " << m_actual_position.z() << bracket.Close;
    return out.str();
}

std::string PointCommand::NormalToString(Brackets brackets)
{
    auto bracket = GetBracket(brackets);
    std::stringstream out {};
    out << bracket.Open << m_normal.x() << ", " << m_normal.y() << ", " << m_normal.z() << bracket.Close;
    return out.str();
}

bool PointCommand::Register()
{
    return m_context->AddObject(this, OnRuntimeContextCallback);
}
