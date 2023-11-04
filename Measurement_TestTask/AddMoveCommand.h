#pragma once

#include <QDialog>

#include "AddCommandBase.h"
#include "BoundCommand.h"
#include "ContextObject.h"
#include "MoveCommand.h"
#include "ui_AddMoveCommand.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddMoveCommandClass; };
QT_END_NAMESPACE

class AddMoveCommand : public QDialog, public AddCommandBase
{
    Q_OBJECT

public:
    AddMoveCommand(QWidget *parent = nullptr, RuntimeContext* context = nullptr) noexcept;
    ~AddMoveCommand() override;

protected:
    void ConstructCommandObject() override;

private:
    Ui::AddMoveCommandClass *ui;

private slots:
    void OnAcceptButtonClicked();
};
