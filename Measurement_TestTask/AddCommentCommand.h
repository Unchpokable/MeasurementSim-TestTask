#pragma once

#include <QDialog>

#include "AddCommandBase.h"
#include "ui_AddCommentCommand.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddCommentCommandClass; };
QT_END_NAMESPACE

class AddCommentCommand : public QDialog, public AddCommandBase
{
    Q_OBJECT

public:
    AddCommentCommand(QWidget *parent = nullptr, RuntimeContext* = nullptr);
    ~AddCommentCommand() override;

    void ConstructCommandObject() override;

private:
    Ui::AddCommentCommandClass *ui;
};
