#include "UMeasure.h"

#include <QMessageBox>
#include <QScrollBar>

#include "AddCircleCenterCommand.h"
#include "AddCircleCommand.h"
#include "AddMoveCommand.h"
#include "AddPlaneCommand.h"
#include "AddPointCommand.h"
#include "CommandListModel.h"


UMeasure::UMeasure(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UMeasureClass())
{
    ui->setupUi(this);
    m_interpreter = new CommandInterpreter();
    
    connect(ui->addMoveButton, &QPushButton::clicked, this, [this]() {
        ShowAddCommandForm(ci_move);
    });

    connect(ui->addPointButton, &QPushButton::clicked, this, [this]() {
        ShowAddCommandForm(ci_point);
    });

    connect(ui->addPlaneButton, &QPushButton::clicked, this, [this]() {
        ShowAddCommandForm(ci_plane);
    });

    connect(ui->addCircleButton, &QPushButton::clicked, this, [this]() {
        ShowAddCommandForm(ci_circle);
    });

    connect(ui->addCircleCenterButton, &QPushButton::clicked, this, [this]() {
        ShowAddCommandForm(ci_circle_to_point);
    });

    connect(ui->startProgramButton, &QPushButton::clicked, this, [this]() {
        ExecuteCommandSequence();
    });

    m_commands_list = new CommandListModel(this);

    ui->programView->setModel(m_commands_list);
}

UMeasure::~UMeasure()
{
    delete ui;
    delete m_interpreter;
}

void UMeasure::ShowAddCommandForm(ContextObjectType cmd_type)
{
    switch (cmd_type)
    {
    case ci_move:
        {
            ShowFormAndAddCreatedCommand<AddMoveCommand>();
            return;
        }
    case ci_point:
        {
            ShowFormAndAddCreatedCommand<AddPointCommand>();
            return;
        }
    case ci_plane:
        {
            ShowFormAndAddCreatedCommand<AddPlaneCommand>();
            return;
        }
    case ci_circle:
        {
            ShowFormAndAddCreatedCommand<AddCircleCommand>();
            return;
        }
    case ci_circle_to_point:
        {
            ShowFormAndAddCreatedCommand<AddCircleCenterCommand>();
            return;
        }
    }
}

void UMeasure::ExecuteCommandSequence() const noexcept
{
    const auto exec_thread = m_interpreter->RunProgramAsync([this](const QString& callback_data) {
        ui->programTextView->append(callback_data + "\n");
    },
    [this](const QString& callback_data) {
        ui->programTextView->append(callback_data + "\n");
    });

    const_cast<std::thread*>(exec_thread)->join();
}


