#ifndef SENSORREPOSITORY_H
#define SENSORREPOSITORY_H

#include "Sensor.h"
#include "sensorcreator.h"
#include <vector>
#include <QString>
#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
class Controller;

class SensorRepository : public QObject
{
    Q_OBJECT

private:
    std::vector<Sensor*> sensors;
    SensorCreator sensorCreator;
    Controller* controller;

public:
    SensorRepository();
    ~SensorRepository();

    void setController(Controller *c);

    // CRUD operations
    void addSensor(Sensor* sensor);
    void removeSensor(unsigned int sensorId);
    Sensor* searchSensor(unsigned int sensorId) const;
    std::vector<Sensor*> getAllSensors() const;
    Sensor* getSensor() const;
    // File operations
    void saveToFile(const QString& filename) const;
    void loadFromFile(const QString& filename);

signals:
    void sensorAdded(Sensor* sensor);
    void sensorRemoved(unsigned int sensorId);
};

#endif // SENSORREPOSITORY_H
