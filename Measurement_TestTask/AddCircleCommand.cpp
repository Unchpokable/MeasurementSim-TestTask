#include "AddCircleCommand.h"

#include <QMessageBox>

#include "CircleCommand.h"

AddCircleCommand::AddCircleCommand(QWidget *parent, RuntimeContext* context)
    : QDialog(parent), AddCommandBase(context)
    , ui(new Ui::AddCircleCommandClass())
{
    ui->setupUi(this);

    connect(ui->acceptButton, &QPushButton::clicked, [this]() {
        ConstructCommandObject();
    });
}

AddCircleCommand::~AddCircleCommand()
{
    delete ui;
}

void AddCircleCommand::ConstructCommandObject()
{
    //TODO: Этот метод - почти полная копия AddPlaneCommand.ConstructCommandObject(). Можно попробовать унифицировать это с помощью шаблонов. А можно и не пробовать
    const auto object_name = ui->objectIdInput->text();

    if(object_name.isEmpty())
        QMessageBox::warning(this, QString("Incorrect input"), QString("Object identifier can not be empty string"));

    std::vector<ContextObject*> args {};
    const std::vector<double> dummy {};

    const auto point1 = m_runtime_context->GetObjectByName(ui->point1Input->text());
    if (point1 == nullptr)
    {
        QMessageBox::warning(this, QString("Warning"),
            QString("No object named" + ui->point1Input->text() + "found in context"));
        return;
    }

    const auto point2 = m_runtime_context->GetObjectByName(ui->point2Input->text());
    if (point2 == nullptr)
    {
        QMessageBox::warning(this, QString("Warning"),
            QString("No object named " + ui->point2Input->text() + " found in context"));
        return;
    }

    const auto point3 = m_runtime_context->GetObjectByName(ui->point3Input->text());
    if(point3 == nullptr)
    {
        QMessageBox::warning(this, QString("Warning"),
            QString("No object named " + ui->point3Input->text() + " found in context"));
        return;
    }

    args.push_back(const_cast<ContextObject*>(point1));
    args.push_back(const_cast<ContextObject*>(point2));
    args.push_back(const_cast<ContextObject*>(point3));

    const auto command = new CircleCommand(object_name);
    const auto bound_command = new BoundCommand(m_runtime_context, command, dummy, args);
    m_constructed_command = bound_command;
    close();
}