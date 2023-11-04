#pragma once

#include <QtWidgets/QMainWindow>

#include "CommandInterpreter.h"
#include "ui_UMeasure.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UMeasureClass; };
QT_END_NAMESPACE

class UMeasure : public QMainWindow
{
    Q_OBJECT

public:
    UMeasure(QWidget *parent = nullptr);
    ~UMeasure();


private:
    Ui::UMeasureClass *ui;
    CommandInterpreter* m_interpreter;
    void ShowAddCommandForm(ContextObjectType cmd_type);
};