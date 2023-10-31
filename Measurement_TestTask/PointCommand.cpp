#include "PointCommand.h"

void PointCommand::Init(const Point3d& initial_pos, const Eigen::Vector3d& normal)
{
    m_nominal_position = initial_pos;
    m_normal = normal;
    m_actual_position = m_nominal_position;
}

void PointCommand::Execute(const std::vector<double>& args)
{
    const auto machine = m_context->GetMeasureMachine();
    m_actual_position = const_cast<MeasureMachine*>(machine)->GetPoint(m_normal, m_nominal_position);
}


QString PointCommand::ToString() {
    std::stringstream out {};

    out << "$POINT(";
    out << "ID::" << m_object_name.toStdString() << ", ";
    out << "CRD::" << NominalToString(BR_ROUND);
    out << "NORM::" << NormalToString(BR_ROUND);

    out << "#{\n";

    out << "NOM:" << NominalToString(BR_ROUND) << NormalToString(BR_SQUARE) << '\n';
    out << "ACT:" << ActualToString(BR_ROUND) << NormalToString(BR_SQUARE) << '\n';
    out << "}";

    return QString::fromUtf8(out.str().c_str());
}

std::string PointCommand::NominalToString(Brackets brackets)
{
    auto bracket = GetBracket(brackets);
    std::stringstream out {};
    out << bracket.Open << m_nominal_position.x << ", " << m_nominal_position.y << ", " << m_nominal_position.z << bracket.Close;
    return out.str();
}

std::string PointCommand::ActualToString(Brackets brackets)
{
    auto bracket = GetBracket(brackets);
    std::stringstream out {};
    out << bracket.Open << m_actual_position.x << ", " << m_actual_position.y << ", " << m_actual_position.z << bracket.Close;
    return out.str();
}

std::string PointCommand::NormalToString(Brackets brackets)
{
    auto bracket = GetBracket(brackets);
    std::stringstream out {};
    out << bracket.Open << m_normal.x << ", " << m_normal.y << ", " << m_normal.z << bracket.Close;
    return out.str();
}

Bracket PointCommand::GetBracket(Brackets brackets)
{
    switch (brackets)
    {
    case BR_ROUND:
        return RoundBrackets();
    case BR_SQUARE:
        return SquareBrackets();
    }

    return RoundBrackets();
}

