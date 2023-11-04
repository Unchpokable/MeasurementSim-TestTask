#include "UMeasure.h"
#include <QtWidgets/QApplication>
#include <QStyleFactory>
#include "UMeasure.h"

// Краткое описание всего нижепроисходящего - "Кодохульство"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));
    UMeasure w;
    w.show();
    return a.exec();
}
