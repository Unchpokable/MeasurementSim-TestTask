#pragma once
#include "CommandBase.h"
#include "ContextObject.h"
#include "RuntimeContext.h"

class MoveCommand : public CommandBase, public ContextObject
{
public:
    MoveCommand(RuntimeContext* context)
    {
        m_context = context;
        SetType(ci_move);
    }
    ~MoveCommand() override
    {
    }

    QString ToString() override;
    void Execute(const std::vector<double>& args) override;

private:
    RuntimeContext* m_context;
};

