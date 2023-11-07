#include "AddCircleCenterCommand.h"

#include "CircleCenterCommand.h"
#include "CircleCommand.h"
#include "DefaultCallbacks.h"
#include "PointCommand.h"


AddCircleCenterCommand::AddCircleCenterCommand(QWidget *parent, RuntimeContext* context)
    : QDialog(parent), AddCommandBase(context)
    , ui(new Ui::AddCircleCenterCommandClass())
{
    ui->setupUi(this);

    connect(ui->acceptButton, &QPushButton::clicked, this, [this]() {
        ConstructCommandObject();
    });
}

AddCircleCenterCommand::~AddCircleCenterCommand()
{
    delete ui;
}

void AddCircleCenterCommand::ConstructCommandObject()
{
    const auto obj_id = ui->objectIdInput->text();

    if(obj_id.isEmpty()) {
        QMessageBox::warning(this, QString("Incorrect input"),
            QString("Object identifier can not be empty string"));
        return;
    }

    const auto target_circle = m_runtime_context->GetObjectByName(ui->targetCircleInput->text());

    if(target_circle == nullptr)
    {
        QMessageBox::warning(this, QString("Invalid input"), QString("Selected circle is not exists"));
        return;
    }

    const auto result_point = new PointCommand(m_runtime_context, obj_id);

    if(!m_runtime_context->AddObject(result_point, OnRuntimeContextCallback))
    {
        QMessageBox::warning(this, QString("Invalid input"), QString("Can not add object to context"));
        return;
    }


    std::vector<ContextObject*> args {};
    const std::vector<double> dummy {};

    args.push_back(const_cast<ContextObject*>(target_circle));

    const auto command = new CircleCenterCommand(obj_id, result_point);
    const auto bound_command = new BoundCommand(m_runtime_context, command, dummy, args);

    m_constructed_command = bound_command;
    close();
}
