#include "AddPlaneCommand.h"
#include <QString>
#include <QMessageBox>

#include "DefaultCallbacks.h"
#include "PlaneCommand.h"

AddPlaneCommand::AddPlaneCommand(QWidget *parent, RuntimeContext* context)
    : QDialog(parent), AddCommandBase(context)
    , ui(new Ui::AddPlaneCommandClass())
{
    ui->setupUi(this);
    connect(ui->acceptButton, &QPushButton::clicked, this, [this]() {
        OnAcceptButtonClicked();
    });
}

AddPlaneCommand::~AddPlaneCommand()
{
    delete ui;
}

void AddPlaneCommand::ConstructCommandObject() {
    const auto id = ui->objectIdInput->text();

    if(id.size() == 0) {
        QMessageBox::warning(this, QString("Warning"),
            QString("Object identifier can not be empty string"));
        return;
    }

    std::vector<ContextObject*> args {};
    std::vector<double> dummy {};

    const auto point1 = m_runtime_context->GetObjectByName(ui->point1Input->text());
    if (point1 == nullptr)
    {
        QMessageBox::warning(this, QString("Warning"),
            QString("No object named" + ui->point1Input->text() + "found in context"));
    }

    const auto point2 = m_runtime_context->GetObjectByName(ui->point2Input->text());
    if (point2 == nullptr)
    {
        QMessageBox::warning(this, QString("Warning"),
            QString("No object named " + ui->point2Input->text() + " found in context"));
    }

    const auto point3 = m_runtime_context->GetObjectByName(ui->point3Input->text());
    if(point3 == nullptr) {
        QMessageBox::warning(this, QString("Warning"),
            QString("No object named " + ui->point3Input->text() + " found in context"));
    }

    args.push_back(const_cast<ContextObject*>(point1));
    args.push_back(const_cast<ContextObject*>(point2));
    args.push_back(const_cast<ContextObject*>(point3));

    const auto command = new PlaneCommand(id);
    const auto bound_command = new BoundCommand(m_runtime_context,
                                                command,
                                                dummy,
                                                args);

    if (!m_runtime_context->AddObject(command, OnRuntimeContextCallback))
    {
        QMessageBox::warning(this, QString("Warning!"),
            QString("Data you have entered is incorrect. Please, check your input and try again"));
        return;
    }

    if (!m_runtime_context->BindDependencies(command, args))
    {
        QMessageBox::warning(this, QString("Warning!"),
            QString("Interpreter can not resolve dependency objects for this plane - some of given points not initialized now and can not be bound with this plane"));

        m_runtime_context->RemoveObject(command->GetName(), OnRuntimeContextCallback);
        return;
    }

    m_constructed_command = bound_command;
    close();
}

void AddPlaneCommand::OnAcceptButtonClicked()
{
    ConstructCommandObject();
}
