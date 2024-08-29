#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include <QObject>
#include <QtCore>
#include <QtCharts>
//#include "Sensor.h"
//#include "SensorRepository.h"

class Controller;


class SimulationManager : public QObject
{
    Q_OBJECT
private:
    Controller* controller;

public:
    SimulationManager();
    ~SimulationManager();


public slots:
    //void runSimulation(Sensor* );
};

#endif // SIMULATIONMANAGER_H
