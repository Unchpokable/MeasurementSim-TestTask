#include "UMeasure.h"
#include <QScrollBar>

#include "AddMoveCommand.h"

UMeasure::UMeasure(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UMeasureClass())
{
    ui->setupUi(this);
    m_interpreter = new CommandInterpreter();
    
    connect(ui->addMoveButton, &QPushButton::clicked, this, [this]() {
        ShowAddCommandForm(ci_move);
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
            const auto form = new AddMoveCommand(this, 
                const_cast<RuntimeContext*>(m_interpreter->GetContext()));
            int ret = form->exec();
            if (form)
            {
                const auto new_command = form->GetConstructedObject();
                m_interpreter->AddCommand(const_cast<BoundCommand*>(new_command));
            }
        }
    }
}

