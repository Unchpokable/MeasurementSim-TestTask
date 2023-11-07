#pragma once

#include <QDialog>

#include "AddCommandBase.h"
#include "ui_AddCircleCenterCommand.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddCircleCenterCommandClass; };
QT_END_NAMESPACE

class AddCircleCenterCommand : public QDialog, public AddCommandBase
{
    Q_OBJECT

public:
    AddCircleCenterCommand(QWidget *parent = nullptr, RuntimeContext* context = nullptr);
    ~AddCircleCenterCommand() override;

    void ConstructCommandObject() override;

private:
    Ui::AddCircleCenterCommandClass *ui;
};
