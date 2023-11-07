#include "AddMoveCommand.h"
#include <QMessageBox>
#include "DefaultCallbacks.h"

AddMoveCommand::AddMoveCommand(QWidget *parent, RuntimeContext* runtime_context) noexcept
    : QDialog(parent), AddCommandBase(runtime_context)
    , ui(new Ui::AddMoveCommandClass())
{
    ui->setupUi(this);
    connect(ui->acceptButton, &QPushButton::clicked, this, [this]() { OnAcceptButtonClicked(); });
}

AddMoveCommand::~AddMoveCommand()
{
    delete ui;
}

void AddMoveCommand::OnAcceptButtonClicked()
{
    ConstructCommandObject();
}

void AddMoveCommand::ConstructCommandObject()
{
    std::vector<double> args_vec{};
    args_vec.push_back(std::stod(ui->xInput->text().toStdString()));
    args_vec.push_back(std::stod(ui->yInput->text().toStdString()));
    args_vec.push_back(std::stod(ui->zInput->text().toStdString()));

    const std::vector<ContextObject*> dummy {};

    const auto command = new MoveCommand(m_runtime_context, QString(
        (std::stringstream {} << "service_object<" << rand() % 65536).str().c_str()));
    const auto bound_command = new BoundCommand(m_runtime_context,
        command,
        args_vec,
        dummy);
    m_constructed_command = bound_command;
    close();
}