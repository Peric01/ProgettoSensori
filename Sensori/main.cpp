#include "sensorviewer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SensorViewer w;
    w.show();
    return a.exec();
}
