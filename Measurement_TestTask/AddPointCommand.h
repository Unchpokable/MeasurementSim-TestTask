#pragma once

#include <QDialog>

#include "AddCommandBase.h"
#include "ui_AddPointCommand.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddPointCommandClass; };
QT_END_NAMESPACE

#define templates

class AddPointCommand : public QDialog, public AddCommandBase
{
    Q_OBJECT
public:
    AddPointCommand(QWidget *parent = nullptr, RuntimeContext* = nullptr);
    ~AddPointCommand() override;

protected:
    void ConstructCommandObject() override;

private:
    Ui::AddPointCommandClass *ui;

private slots:
    void OnAcceptButtonClicked();
};
