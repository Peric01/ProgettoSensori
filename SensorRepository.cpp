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

Sensor* SensorRepository::getSensor() const{

    if(sensors.empty())
        throw std::runtime_error("Nessun sensore disponibile");
    return *(sensors.begin());
}

Sensor* SensorRepository::searchSensor(unsigned int sensorId) const {
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

void SensorRepository::loadFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Couldn't open the file.");
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    QJsonObject jsonObj = doc.object();

    // Caricamento sensori di temperatura
    QJsonArray temperatureArray = jsonObj["temperatureSensors"].toArray();
    for (const QJsonValue &value : temperatureArray) {
        QJsonObject obj = value.toObject();
        Sensor* sensor = new TempSensor(
            obj["id"].toInt(),
            obj["name"].toString(),
            static_cast<float>(obj["value"].toDouble())  // Conversione a float
            );
        sensors.push_back(sensor);
    }

    // Caricamento sensori di torbidità
    QJsonArray turbidityArray = jsonObj["turbiditySensors"].toArray();
    for (const QJsonValue &value : turbidityArray) {
        QJsonObject obj = value.toObject();
        Sensor* sensor = new TurbSensor(
            obj["id"].toInt(),
            obj["name"].toString(),
            obj["value"].toDouble()
            );
        sensors.push_back(sensor);
    }

    // Caricamento sensori di pH
    QJsonArray phArray = jsonObj["phSensors"].toArray();
    for (const QJsonValue &value : phArray) {
        QJsonObject obj = value.toObject();
        Sensor* sensor = new PHSensor(
            obj["id"].toInt(),
            obj["name"].toString(),
            obj["value"].toDouble()
            );
        sensors.push_back(sensor);
    }
}
