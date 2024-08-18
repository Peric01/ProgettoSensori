#include "SensorRepository.h"
#include <fstream>

SensorRepository::SensorRepository() {
    sensorCreator = SensorCreator();
}

SensorRepository::~SensorRepository() {
    for (Sensor* sensor : sensors) {
        delete sensor;
    }
    sensors.clear();
}

void SensorRepository::addSensor(Sensor* sensor) {
    sensors.push_back(sensor);
    emit sensorAdded(sensor);
}

void SensorRepository::removeSensor(unsigned int sensorId) {
    for (auto it = sensors.begin(); it != sensors.end(); ++it) {
        if ((*it)->getID() == sensorId) {
            delete *it;
            sensors.erase(it);
            emit sensorRemoved(sensorId);
            break;
        }
    }
}

Sensor* SensorRepository::getSensor(unsigned int sensorId) const {
    for (const auto& sensor : sensors) {
        if (sensor->getID() == sensorId) {
            return sensor;
        }
    }
    return nullptr;
}

std::vector<Sensor*> SensorRepository::getAllSensors() const {
    return sensors;
}

void SensorRepository::saveToFile(const QString& filename) const {
    std::ofstream file(filename.toStdString());
    if (file.is_open()) {
        for (const auto& sensor : sensors) {
            file << sensor->toString() << std::endl;
        }
        file.close();
    }
}

void SensorRepository::loadFromFile(const QString& filename) {
    std::ifstream file(filename.toStdString());
    if (file.is_open()) {
        sensors.clear();
        std::string line;
        while (std::getline(file, line)) {
            Sensor* newSensor = sensorCreator.createSensorFromData(line);
            sensors.push_back(newSensor);
        }
        file.close();
    }
}
