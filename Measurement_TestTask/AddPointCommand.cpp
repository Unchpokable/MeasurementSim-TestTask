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
    const QString id(ui->objectIdInput->text());

    if (id.size() == 0)
    {
        QMessageBox::warning(this, QString("Warning"), QString("Object identifier can not be empty"));
        return;
    }

    std::vector<double> args(6);
    const std::vector<ContextObject*> dummy {};

    args.push_back(std::stod(ui->xInput->text().toStdString()));
    args.push_back(std::stod(ui->yInput->text().toStdString()));
    args.push_back(std::stod(ui->zInput->text().toStdString()));

    args.push_back(std::stod(ui->iNormalInput->text().toStdString()));
    args.push_back(std::stod(ui->jNormalInput->text().toStdString()));
    args.push_back(std::stod(ui->kNormalInput->text().toStdString()));

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
