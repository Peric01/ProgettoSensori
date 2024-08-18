#ifndef MODEL_H
#define MODEL_H

#include "Sensor.h"
#include "sensorcreator.h"
#include <vector>
#include <QString>
#include <QObject>

class Model : public QObject
{
    Q_OBJECT

private:
    std::vector<Sensor*> sensors;
    SensorCreator sensorCreator;

public:
    Model();
    ~Model();

    // CRUD operations
    void addSensor(Sensor*);
    void removeSensor(unsigned int);
    Sensor* getSensor(unsigned int) const;
    std::vector<Sensor*> getAllSensors() const;

    // File operations
    void saveToFile(const QString&) const;
    void loadFromFile(const QString&);

    // Simulation
    void runSimulation(unsigned int);
    void restartSimulation(unsigned int);

    // Data management
    void removeValue(unsigned int , size_t);
    void clearValues(unsigned int);

signals:
    void sensorAdded(Sensor*);
    void sensorRemoved(unsigned int);
    void sensorUpdated(Sensor*);
    void simulationCompleted(unsigned int);
    void dataCleared(unsigned int);

public slots:
    void onSimulationRequested(unsigned int);
};

#endif // MODEL_H
