#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include "Sensor.h"
#include <QObject>

class SimulationManager : public QObject
{
    Q_OBJECT

public:
    SimulationManager();
    ~SimulationManager();

    // Simulation
    void runSimulation(Sensor* sensor);

    // Data management
    void removeValue(Sensor* sensor, size_t index);
    void clearValues(Sensor* sensor);

signals:
    void simulationCompleted(unsigned int sensorId);
    void dataCleared(unsigned int sensorId);
    void sensorUpdated(Sensor* sensor);

public slots:
    //void onSimulationRequested(unsigned int sensorId);
};

#endif // SIMULATIONMANAGER_H
