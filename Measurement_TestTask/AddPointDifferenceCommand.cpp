#include "AddPointDifferenceCommand.h"

#include <QMessageBox>
#include "Formats.h"
#include "ReportPointCommand.h"

AddPointDifferenceCommand::AddPointDifferenceCommand(QWidget *parent, RuntimeContext* context)
    : QDialog(parent), AddCommandBase(context)
    , ui(new Ui::AddPointDifferenceCommandClass())
{
    ui->setupUi(this);

    connect(ui->acceptButton, &QPushButton::clicked, this, [this]() {
        ConstructCommandObject();
    });
}

AddPointDifferenceCommand::~AddPointDifferenceCommand()
{
    delete ui;
}

void AddPointDifferenceCommand::ConstructCommandObject()
{
    const auto target_point = m_runtime_context->GetObjectByName(ui->pointInput->text());
    if (target_point == nullptr)
    {
        QMessageBox::warning(this, "Incorrect input", "Given point is not exists");
        return;
    }

    double diff_threshold;

    try
    {
        diff_threshold = std::stod(ui->thresholdInput->text().toStdString());
    }
    catch(const std::exception&) 
    {
        QMessageBox::warning(this, "Incorrect input", "Entered number is not a valid number");
        return;
    }

    if (diff_threshold < 0)
    {
        QMessageBox::warning(this, "Incorrect input", "Difference threshold can not be less than 0");
        return;
    }

    const auto command = new ReportPointCommand(RandomString(10), diff_threshold);

    m_constructed_command = new BoundCommand(m_runtime_context, command, 
                                            std::vector<double>{}, 
                                            std::vector{const_cast<ContextObject*>(target_point)});
    close();
}
