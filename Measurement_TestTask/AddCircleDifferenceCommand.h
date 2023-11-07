#pragma once

#include <QDialog>

#include "AddCommandBase.h"
#include "ui_AddCircleDifferenceCommand.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddCircleDifferenceCommandClass; };
QT_END_NAMESPACE

class AddCircleDifferenceCommand : public QDialog, public AddCommandBase
{
    Q_OBJECT

public:
    AddCircleDifferenceCommand(QWidget *parent = nullptr, RuntimeContext* context = nullptr);
    ~AddCircleDifferenceCommand() override;

    void ConstructCommandObject() override;

private:
    Ui::AddCircleDifferenceCommandClass *ui;
};
