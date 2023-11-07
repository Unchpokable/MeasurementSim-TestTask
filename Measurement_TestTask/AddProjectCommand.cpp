#include "AddProjectCommand.h"

#include <QMessageBox>

#include "DefaultCallbacks.h"
#include "ProjectCommand.h"

AddProjectCommand::AddProjectCommand(QWidget *parent, RuntimeContext* context)
    : QDialog(parent), AddCommandBase(context)
    , ui(new Ui::AddProjectCommandClass())
{
    ui->setupUi(this);

    connect(ui->acceptButton, &QPushButton::clicked, this, [this]() {
        ConstructCommandObject();
    });
}

AddProjectCommand::~AddProjectCommand()
{
    delete ui;
}

void AddProjectCommand::ConstructCommandObject()
{
    const auto obj_id = ui->objectIdInput->text();

    if (obj_id.isEmpty())
    {
        QMessageBox::warning(this, QString("Incorrect input"), 
            QString("Object identifier can not be empty string"));
        return;
    }


    const auto target_point = m_runtime_context->GetObjectByName(ui->pointInput->text());
    if(target_point == nullptr)
    {
        QMessageBox::warning(this, QString("Incorrect input"), 
            QString("Given point does not exists"));
        return;
    }

    const auto target_plane = m_runtime_context->GetObjectByName(ui->planeInput->text());

    if(target_plane == nullptr)
    {
        QMessageBox::warning(this, QString("Incorrect input"), 
            QString("Given plane does not exists"));
        return;
    }

    const auto result_point = new PointCommand(m_runtime_context, obj_id);

    if(!m_runtime_context->AddObject(result_point, OnRuntimeContextCallback)) {
        QMessageBox::warning(this, QString("Invalid input"), QString("Can not add object to context"));
        return;
    }

    const std::vector<double> dummy {};
    std::vector<ContextObject*> args {};

    args.push_back(const_cast<ContextObject*>(target_point));
    args.push_back(const_cast<ContextObject*>(target_plane));

    const auto command = new ProjectCommand(obj_id, result_point);

    m_constructed_command = new BoundCommand(m_runtime_context, command, dummy, args);
    close();
}

