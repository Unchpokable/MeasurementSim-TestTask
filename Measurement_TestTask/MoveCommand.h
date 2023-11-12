#pragma once
#include "CommandBase.h"
#include "ContextObject.h"
#include "RuntimeContext.h"

class MoveCommand : public CommandBase, public ContextObject
{
public:
    MoveCommand(RuntimeContext* context, QString name) : ContextObject(name, ci_move)
    {
        m_context = context;
    }
    ~MoveCommand() override
    {
    }

    QString ToString() override;
    QString ToPrettyString() override;
    void Execute(const std::vector<double>& args) override;

private:
    RuntimeContext* m_context;
    std::vector<double> target_position { 0, 0, 0 };
};

