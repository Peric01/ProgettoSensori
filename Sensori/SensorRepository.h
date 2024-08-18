#ifndef SENSORREPOSITORY_H
#define SENSORREPOSITORY_H

#include "Sensor.h"
#include "sensorcreator.h"
#include <vector>
#include <QString>
#include <QObject>

class SensorRepository : public QObject
{
    Q_OBJECT

private:
    std::vector<Sensor*> sensors;
    SensorCreator sensorCreator;

public:
    SensorRepository();
    ~SensorRepository();

    // CRUD operations
    void addSensor(Sensor* sensor);
    void removeSensor(unsigned int sensorId);
    Sensor* getSensor(unsigned int sensorId) const;
    std::vector<Sensor*> getAllSensors() const;

    // File operations
    void saveToFile(const QString& filename) const;
    void loadFromFile(const QString& filename);

signals:
    void sensorAdded(Sensor* sensor);
    void sensorRemoved(unsigned int sensorId);
};

#endif // SENSORREPOSITORY_H
