#pragma once

#include <QDialog>

#include "AddCommandBase.h"
#include "ui_AddCircleCommand.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddCircleCommandClass; };
QT_END_NAMESPACE

class AddCircleCommand : public QDialog, public AddCommandBase
{
    Q_OBJECT

public:
    AddCircleCommand(QWidget *parent = nullptr, RuntimeContext* context = nullptr);
    ~AddCircleCommand() override;

    void ConstructCommandObject() override;

private:
    Ui::AddCircleCommandClass *ui;
};
