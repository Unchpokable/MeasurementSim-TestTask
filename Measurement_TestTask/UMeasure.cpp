#include "UMeasure.h"
#include <QScrollBar>

UMeasure::UMeasure(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UMeasureClass())
{
    ui->setupUi(this);
}

UMeasure::~UMeasure()
{
    delete ui;
}
