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
    void addSensor(std::string& type);
    void removeSensor(unsigned int sensorId);
    Sensor* getSensor(unsigned int sensorId) const;
    std::vector<Sensor*> getAllSensors() const;

    // File operations
    void saveToFile(const QString& filename) const;
    void loadFromFile(const QString& filename);

    // Simulation
    void runSimulation(unsigned int sensorId);
    void restartSimulation(unsigned int sensorId);

    // Data management
    void removeValue(unsigned int sensorId, size_t index);
    void clearValues(unsigned int sensorId);

signals:
    void sensorAdded(Sensor* sensor);
    void sensorRemoved(unsigned int sensorId);
    void sensorUpdated(Sensor* sensor);
    void simulationCompleted(unsigned int sensorId);
    void dataCleared(unsigned int sensorId);

public slots:
    void onSimulationRequested(unsigned int sensorId);
};

#endif // MODEL_H
