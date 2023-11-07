#pragma once

#include <QDialog>

#include "AddCommandBase.h"
#include "ui_AddProjectCommand.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddProjectCommandClass; };
QT_END_NAMESPACE

class AddProjectCommand : public QDialog, public AddCommandBase
{
    Q_OBJECT

public:
    AddProjectCommand(QWidget *parent = nullptr, RuntimeContext* context = nullptr);
    ~AddProjectCommand() override;

    void ConstructCommandObject() override;

private:
    Ui::AddProjectCommandClass *ui;
};
