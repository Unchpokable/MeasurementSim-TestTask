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
    if(id.size() == 0) 
    {
        QMessageBox::warning(this, QString("Warning"), QString("Object identifier can not be empty"));
        return;
    }

    std::vector<double> args{};
    const std::vector<ContextObject*> dummy {};
    try
    {
        args.push_back(std::stod(ui->xInput->text().toStdString()));
        args.push_back(std::stod(ui->yInput->text().toStdString()));
        args.push_back(std::stod(ui->zInput->text().toStdString()));
    }
    catch (const std::exception&)
    {
        QMessageBox::warning(this, "Incorrect input", "Given value is not a number");
        return;
    }

    try
    {
        Eigen::Vector3d normal
        {
            std::stod(ui->iNormalInput->text().toStdString()),
            std::stod(ui->jNormalInput->text().toStdString()),
            std::stod(ui->kNormalInput->text().toStdString())
        };
        normal.normalize();

        args.push_back(normal.x());
        args.push_back(normal.y());
        args.push_back(normal.z());
    }
    catch (const std::exception&)
    {
        QMessageBox::warning(this, "Incorrect Input", "Given value is not a number");
        return;
    }

    const auto command = new PointCommand(m_runtime_context, id);
    
    const auto bound_command = new BoundCommand(m_runtime_context,
        command,
        args,
        dummy);
    m_constructed_command = bound_command;
    close();
}

void AddPointCommand::OnAcceptButtonClicked()
{
    ConstructCommandObject();
}
