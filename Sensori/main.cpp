#include "SensorViewer.h"
#include "Controller.h"
#include "SensorRepository.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QIcon appIcon(":/iconbacterias.ico");
    a.setWindowIcon(appIcon);
    a.setWindowIcon(appIcon);
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
