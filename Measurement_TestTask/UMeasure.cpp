#include "UMeasure.h"
#include <QScrollBar>

#include "AddMoveCommand.h"
#include "AddPlaneCommand.h"
#include "AddPointCommand.h"


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
        }
    }
}

