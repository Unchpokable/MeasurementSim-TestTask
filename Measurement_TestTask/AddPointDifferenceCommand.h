#pragma once

#include <QDialog>

#include "AddCommandBase.h"
#include "ui_AddPointDifferenceCommand.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddPointDifferenceCommandClass; };
QT_END_NAMESPACE

class AddPointDifferenceCommand : public QDialog, public AddCommandBase
{
    Q_OBJECT

public:
    AddPointDifferenceCommand(QWidget *parent = nullptr, RuntimeContext* context = nullptr);
    ~AddPointDifferenceCommand() override;

    void ConstructCommandObject() override;

private:
    Ui::AddPointDifferenceCommandClass *ui;
};
