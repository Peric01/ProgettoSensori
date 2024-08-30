#include "SensorViewer.h"
#include "Controller.h"
#include "SensorRepository.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SensorViewer w;
    Controller c;
    SensorRepository r;
    w.showSensorLists(r.getAllSensors()); // serve per aggiornare la vista appena parte e mettere i colori
    c.setView(&w);
    c.setRepo(&r);
    w.setController(&c);
    w.show();
    return a.exec();
}
