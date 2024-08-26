#include "sensorviewer.h"
#include "Controller.h"
#include "SensorRepository.h"
#include "SimulationManager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SensorViewer w;
    Controller c;
    SensorRepository r;
    SimulationManager m;
    c.setView(&w);
    c.setRepo(&r);
    c.setManager(&m);
    w.setController(&c);
    w.show();
    return a.exec();
}
