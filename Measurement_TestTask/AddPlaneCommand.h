#pragma once

#include <QDialog>

#include "AddCommandBase.h"
#include "ui_AddPlaneCommand.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddPlaneCommandClass; };
QT_END_NAMESPACE

class AddPlaneCommand : public QDialog, public AddCommandBase
{
    Q_OBJECT

public:
    AddPlaneCommand(QWidget *parent = nullptr, RuntimeContext* context = nullptr);
    ~AddPlaneCommand() override;

protected:
    void ConstructCommandObject() override;

private:
    Ui::AddPlaneCommandClass *ui;

private slots:
    void OnAcceptButtonClicked();
};
