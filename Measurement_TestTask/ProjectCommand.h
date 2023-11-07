#pragma once
#include "CommandBase.h"
#include "GeometryData.h"
#include "PlaneCommand.h"
#include "PointCommand.h"
#include "Formats.h"

class ProjectCommand : public CommandBase, public ContextObject
{
public:
    ProjectCommand(const QString& obj_name, PointCommand* result_point) :
        ContextObject(QString(obj_name) + "_autogen_<" 
                                             + RandomString(5) + ">", ci_project),
        m_display_name(obj_name)
    {
        m_result_point = result_point;
    }

    void Execute(const std::vector<ContextObject*>& args) override;
    QString ToString() override;
    QString ToPrettyString() override;

private:
    PointCommand* m_result_point;
    PointCommand* m_root;
    PlaneCommand* m_plane;

    QString m_display_name;
};

