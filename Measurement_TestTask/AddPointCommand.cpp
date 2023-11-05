#include "AddPointCommand.h"

#include "DefaultCallbacks.h"
#include "PointCommand.h"

AddPointCommand::AddPointCommand(QWidget *parent, RuntimeContext* context)
    : QDialog(parent), AddCommandBase(context)
    , ui(new Ui::AddPointCommandClass())
{
    ui->setupUi(this);

    connect(ui->acceptButton, &QPushButton::clicked, this, [this]() {
        OnAcceptButtonClicked();
    });
}

AddPointCommand::~AddPointCommand()
{
    delete ui;
}

void AddPointCommand::ConstructCommandObject()
{
    std::vector<double> args(3);
    const std::vector<ContextObject*> dummy {};

    const QString id(ui->objectIdInput->text());

    args.push_back(std::stod(ui->xInput->text().toStdString()));
    args.push_back(std::stod(ui->yInput->text().toStdString()));
    args.push_back(std::stod(ui->zInput->text().toStdString()));

    const auto command = new PointCommand(m_runtime_context, id);

    const auto bound_command = new BoundCommand(m_runtime_context,
        command,
        args,
        dummy);

    if (m_runtime_context->AddObject(command, OnRuntimeContextCallback))
    {
        m_constructed_command = bound_command;
        close();
    }

    else
    {
        QMessageBox::warning(this, QString::fromUtf8("Warning!"), 
            QString::fromUtf8("Data you have entered is incorrect. Please, check your input and try again"));
    }
}


void AddPointCommand::OnAcceptButtonClicked()
{
    ConstructCommandObject();
}
