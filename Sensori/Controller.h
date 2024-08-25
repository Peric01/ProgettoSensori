#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include "SensorViewer.h"
#include "SimulationManager.h"
#include "SensorRepository.h"


class Controller : public QObject
{
    Q_OBJECT
private:
    bool autoMode;
    QTimer* timer;

    SensorViewer* view;
    SensorRepository* Repo;
    SimulationManager* Manager;
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    void setRepo(SensorRepository* r);
    void setManager(SimulationManager* m);
    void setView(SensorViewer* v);
    void show();
    void add();
    void remove();
    void Simulation();
    void selectSensor();
    //show
    //add
    //remove
    //Simulation
    //seleziona sensore

signals:
};

#endif // CONTROLLER_H
