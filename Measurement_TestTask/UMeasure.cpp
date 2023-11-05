#include "UMeasure.h"
#include <QScrollBar>

#include "AddMoveCommand.h"
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
}

UMeasure::~UMeasure()
{
    delete ui;
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
    }
}

