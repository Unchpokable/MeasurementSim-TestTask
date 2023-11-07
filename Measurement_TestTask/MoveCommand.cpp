#include "MoveCommand.h"

#include <iomanip>

void MoveCommand::Execute(const std::vector<double>& args)
{
    auto machine = const_cast<MeasureMachine*>(m_context->GetMeasureMachine());

    if(args.size() != 3)
        throw std::invalid_argument("Move command awaits 3 arguments - X, Y and Z coordinate of new position");

    const Point3d new_position(args[0], args[1], args[2]);
    machine->SetPosition(new_position);

    std::stringstream cb {};
    cb << "MOVED TO " << machine->GetProbePosition() << "\n";
    Emit(this);
}

QString MoveCommand::ToString()
{
    std::stringstream out {};
    auto probe = m_context->GetMeasureMachine()->GetProbePosition();

    out << "$MOVE(" << probe.x() << "," << probe.y() << "," << probe.z() << ")\n";

    return QString::fromUtf8(out.str().c_str());
}

QString MoveCommand::ToPrettyString()
{
    std::stringstream out {};

    auto probe = m_context->GetMeasureMachine()->GetProbePosition();
    out << std::fixed << std::setprecision(3);
    out << "Moved measurement probe to (" << probe.x() << ", " << probe.y() << ", " << probe.z() << ")\n\n";

    return QString::fromUtf8(out.str());
}
