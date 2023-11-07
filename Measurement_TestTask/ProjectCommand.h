#pragma once
#include "CommandBase.h"
#include "GeometryData.h"
#include "PlaneCommand.h"
#include "PointCommand.h"

class ProjectCommand : public CommandBase, public ContextObject
{
public:
    ProjectCommand(const QString& obj_name) : ContextObject(obj_name, ci_project)
    {
        SetType(ci_project);
        m_object_name = obj_name;
    }

    void Execute(const std::vector<ContextObject*>& args) override;
    QString ToString() override;
    QString ToPrettyString() override;

    const ProjectionPoint3d& GetProjectedPoint();

private:
    ProjectionPoint3d m_projection;
    PointCommand* m_root;
    PlaneCommand* m_plane;
};

