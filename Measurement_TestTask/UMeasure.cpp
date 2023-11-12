#include "UMeasure.h"

#include <QMessageBox>
#include <QScrollBar>

#include "AddCircleCenterCommand.h"
#include "AddCircleCommand.h"
#include "AddCircleDifferenceCommand.h"
#include "AddCommentCommand.h"
#include "AddMoveCommand.h"
#include "AddPlaneCommand.h"
#include "AddPointCommand.h"
#include "AddPointDifferenceCommand.h"
#include "AddProjectCommand.h"
#include "CommandListModel.h"
#include "CommentCommand.h"


UMeasure::UMeasure(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UMeasureClass())
{
    ui->setupUi(this);
    m_interpreter = new CommandInterpreter();

    connect(ui->addCommentButton, &QPushButton::clicked, this, [this]() {
        ShowAddCommandForm(ci_comment);
    });

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

    connect(ui->addProjectPlane2PointButton, &QPushButton::clicked, this, [this]() {
        ShowAddCommandForm(ci_project);
    });

    connect(ui->addDiffPointButton, &QPushButton::clicked, this, [this]() {
        ShowAddCommandForm(ci_point_diff);
    });

    connect(ui->addDiffCircleButton, &QPushButton::clicked, this, [this]() {
        ShowAddCommandForm(ci_circle_diff);
    });

    connect(ui->startProgramButton, &QPushButton::clicked, this, [this]() {
        ExecuteCommandSequence();
    });

    connect(this, &UMeasure::OutputReceived, this, &UMeasure::OnOutputReceived);

    m_commands_list = new CommandListModel(this);

    ui->programView->setModel(m_commands_list);

    AddProgramViewContextMenu();
}

UMeasure::~UMeasure()
{
    delete ui;
    delete m_interpreter;
}

void UMeasure::AddProgramViewContextMenu() noexcept
{
    contextMenu = new QMenu();

    const auto deleteAction = new QAction("Remove", this);
    connect(deleteAction, &QAction::triggered, this, &UMeasure::OnDeleteAction);
    contextMenu->addAction(deleteAction);

    const auto replaceMenu = new QMenu("Replace", this);
    contextMenu->addMenu(replaceMenu);

    const auto insertAfter = new QMenu("Insert new command after", this);
    const auto insertBefore = new QMenu("Insert new command before", this);

    contextMenu->addMenu(insertAfter);
    contextMenu->addMenu(insertBefore);

    ui->programView->setContextMenuPolicy(Qt::CustomContextMenu);

    //TODO: Ёто пиз*ец. пиз*ец должен быть решен.  ак нибудь.
    AddInsertActionToMenu(replaceMenu, "Comment", ci_comment, ip_replace);
    AddInsertActionToMenu(replaceMenu, "Move", ci_move, ip_replace);
    AddInsertActionToMenu(replaceMenu, "Point", ci_point, ip_replace);
    AddInsertActionToMenu(replaceMenu, "Plane", ci_plane, ip_replace);
    AddInsertActionToMenu(replaceMenu, "Circle", ci_circle, ip_replace);
    AddInsertActionToMenu(replaceMenu, "CircleCenter", ci_circle_to_point, ip_replace);
    AddInsertActionToMenu(replaceMenu, "Projection", ci_project, ip_replace);
    AddInsertActionToMenu(replaceMenu, "Report Point", ci_point_diff, ip_replace);
    AddInsertActionToMenu(replaceMenu, "Report Circle", ci_circle_diff, ip_replace);

    AddInsertActionToMenu(insertAfter, "Comment", ci_comment, ip_after);
    AddInsertActionToMenu(insertAfter, "Move", ci_move, ip_after);
    AddInsertActionToMenu(insertAfter, "Point", ci_point, ip_after);
    AddInsertActionToMenu(insertAfter, "Plane", ci_plane, ip_after);
    AddInsertActionToMenu(insertAfter, "Circle", ci_circle, ip_after);
    AddInsertActionToMenu(insertAfter, "CircleCenter", ci_circle_to_point, ip_after);
    AddInsertActionToMenu(insertAfter, "Projection", ci_project, ip_after);
    AddInsertActionToMenu(insertAfter, "Report Point", ci_point_diff, ip_after);
    AddInsertActionToMenu(insertAfter, "Report Circle", ci_circle_diff, ip_after);


    AddInsertActionToMenu(insertBefore, "Comment", ci_comment, ip_before);
    AddInsertActionToMenu(insertBefore, "Move", ci_move, ip_before);
    AddInsertActionToMenu(insertBefore, "Point", ci_point, ip_before);
    AddInsertActionToMenu(insertBefore, "Plane", ci_plane, ip_before);
    AddInsertActionToMenu(insertBefore, "Circle", ci_circle, ip_before);
    AddInsertActionToMenu(insertBefore, "CircleCenter", ci_circle_to_point, ip_before);
    AddInsertActionToMenu(insertBefore, "Projection", ci_project, ip_before);
    AddInsertActionToMenu(insertBefore, "Report Point", ci_point_diff, ip_before);
    AddInsertActionToMenu(insertBefore, "Report Circle", ci_circle_diff, ip_before);

    connect(ui->programView, &QListView::customContextMenuRequested, this, &UMeasure::OnCustomContextMenuRequested);
}

BoundCommand* UMeasure::GetCommandByType(ContextObjectType type)
{
    switch(type)
    {
        case ci_comment:
        {
            return ShowFormCreateCommand<AddCommentCommand>();
        }
        case ci_move:
        {
            return ShowFormCreateCommand<AddMoveCommand>();

        }
        case ci_point:
        {
            return ShowFormCreateCommand<AddPointCommand>();

        }
        case ci_plane:
        {
            return ShowFormCreateCommand<AddPlaneCommand>();

        }
        case ci_circle:
        {
            return ShowFormCreateCommand<AddCircleCommand>();

        }
        case ci_circle_to_point:
        {
            return ShowFormCreateCommand<AddCircleCenterCommand>();

        }
        case ci_project:
        {
            return ShowFormCreateCommand<AddProjectCommand>();

        }
        case ci_point_diff:
        {
            return ShowFormCreateCommand<AddPointDifferenceCommand>();

        }
        case ci_circle_diff:
        {
            return ShowFormCreateCommand<AddCircleDifferenceCommand>();

        }

        case ci_undefined:
            return nullptr;
    }
    return nullptr;
}


void UMeasure::ShowAddCommandForm(ContextObjectType cmd_type)
{
    AddCommand(GetCommandByType(cmd_type));
}

void UMeasure::ExecuteCommandSequence() noexcept
{
    ui->programTextView->clear();
    const auto exec_thread = m_interpreter->RunProgramAsync([this](const QString& callback_data) {
        ui->programTextView->append(callback_data + "\n");
    },
    [this](const QString& callback_data) {
        emit OutputReceived(callback_data);
    });

    const_cast<std::thread*>(exec_thread)->join();
}

void UMeasure::AddCommand(BoundCommand* cmd)
{
    if(cmd == nullptr)
        return;
    m_interpreter->AddCommand(cmd);
    cmd->Execute();
    m_commands_list->addObject(cmd);
    
}

void UMeasure::ReplaceCommand(BoundCommand* cmd, std::size_t position)
{
    if(position < 0 || position >= m_interpreter->GetCommandsCount())
        throw std::invalid_argument("Index was out of bound");

    if (!m_interpreter->ReplaceCommand(cmd, position))
    {
        QMessageBox::warning(this, "Error!", "Unable to replace command");
        return;
    }
    ui->programView->update();
}

void UMeasure::RemoveCommand(std::size_t position)
{
    m_interpreter->RemoveCommand(position);
    ui->programView->update();
}



void UMeasure::OnOutputReceived(const QString& what) const noexcept
{
    ui->programTextView->append(what);
}

void UMeasure::OnDeleteAction()
{
    const auto index = ui->programView->currentIndex();
    const auto row = index.row();

    const auto selected_command = m_interpreter->At(row);
    if (dynamic_cast<ContextObject*>(selected_command->GetCommandObject())->HasTopLevelDependency())
    {
        QMessageBox::warning(this, "Error!", "Selected object has top-level dependencies and can not be removed or replaced");
        return;
    }

    m_commands_list->removeObject(row);
    if (!m_interpreter->RemoveCommand(row))
    {
        QMessageBox::warning(this, "Error!", "Unable to remove selected command");
    }
}

void UMeasure::OnReplaceAction(ContextObjectType type)
{
    const auto index = ui->programView->currentIndex();
    const auto row = index.row();

    const auto selected_command = m_interpreter->At(row);
    if(dynamic_cast<ContextObject*>(selected_command->GetCommandObject())->HasTopLevelDependency()) 
    {
        QMessageBox::warning(this, "Error!", "Selected object has top-level dependencies and can not be removed or replaced");
        return;
    }

    const auto command = GetCommandByType(type);
    if(command == nullptr)
        return;
    command->Execute();
    if (!m_interpreter->ReplaceCommand(command, row))
    {
        QMessageBox::warning(this, "Error!", "Error while replacing command");
        return;
    }

    m_commands_list->replaceObject(row, command);
}

void UMeasure::AddInsertActionToMenu(QMenu* menu, const QString& title, ContextObjectType type, InsertionPosition pos)
{
    const auto action = new QAction(title, this);

    switch (pos)
    {
    case ip_after:
        {
            connect(action, &QAction::triggered, [this, type]() {
                InsertNewCommandAfter(type);
            });
            break;
        }
    case ip_before:
        {
            connect(action, &QAction::triggered, [this, type]() {
                InsertNewCommandBefore(type);
            });
            break;
        }

    case ip_replace:
        {
            connect(action, &QAction::triggered, this, [this, type]() {
                OnReplaceAction(type);
            });
            break;
        }
    }

    connect(action, &QAction::triggered, [this, type]() {

    });

    menu->addAction(action);
}

void UMeasure::InsertNewCommandBefore(ContextObjectType type)
{
    const auto index = ui->programView->currentIndex();
    int row = index.row();

    const auto command = GetCommandByType(type);
    if(command == nullptr)
        return;
    command->Execute();
    if (!m_interpreter->InsertCommand(row, command))
    {
        QMessageBox::warning(this, "Error!", "Unable to insert command");
        return;
    }
    m_commands_list->insertObject(row, command);
}

void UMeasure::InsertNewCommandAfter(ContextObjectType type)
{
    const auto index = ui->programView->currentIndex();
    int row = index.row() - 1;

    if(index.row() < m_interpreter->GetCommandsCount()) 
    {
        row = index.row() + 1;
    }

    const auto command = GetCommandByType(type);
    if(command == nullptr)
        return;
    command->Execute();

    if (!m_interpreter->InsertCommand(row, command))
    {
        QMessageBox::warning(this, "Error!", "Unable to insert command");
        return;
    }
    m_commands_list->insertObject(row, command);
}

