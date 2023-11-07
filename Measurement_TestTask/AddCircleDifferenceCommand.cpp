#include "AddCircleDifferenceCommand.h"

#include <QMessageBox>

#include "Formats.h"
#include "ReportCircleCommand.h"

AddCircleDifferenceCommand::AddCircleDifferenceCommand(QWidget *parent, RuntimeContext* context)
    : QDialog(parent), AddCommandBase(context)
    , ui(new Ui::AddCircleDifferenceCommandClass())
{
    ui->setupUi(this);

    connect(ui->acceptButton, &QPushButton::clicked, this, [this]() {
        ConstructCommandObject();
    });
}

AddCircleDifferenceCommand::~AddCircleDifferenceCommand()
{
    delete ui;
}

void AddCircleDifferenceCommand::ConstructCommandObject()
{
    const auto target_circle = m_runtime_context->GetObjectByName(ui->circleInput->text());

    if (target_circle == nullptr)
    {
        QMessageBox::warning(this, "Incorrect input", "Given circle does not exists");
        return;
    }

    double pos_diff_threshold;
    double radius_diff_threshold;

    try
    {
        radius_diff_threshold = std::stod(ui->thresholdInput->text().toStdString());
    }
    catch(const std::exception&)
    {
        QMessageBox::warning(this, "Incorrect input", "Entered number is not a valid number");
        return;
    }

    try 
    {
        pos_diff_threshold = std::stod(ui->thresholdInput->text().toStdString());
    } catch(const std::exception&) 
    {
        QMessageBox::warning(this, "Incorrect input", "Entered number is not a valid number");
        return;
    }

    const auto command = new ReportCircleCommand(RandomString(10), pos_diff_threshold, radius_diff_threshold);

    m_constructed_command = new BoundCommand(m_runtime_context, command,
        std::vector<double>{},
        std::vector {const_cast<ContextObject*>(target_circle) });

    close();
}
