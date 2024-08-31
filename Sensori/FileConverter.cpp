#include "FileConverter.h"
#include "TempSensor.h"
#include "PHSensor.h"
#include "TurbSensor.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>


QJsonObject FileConverter::SensorToJsonObject(const Sensor& s){
    QJsonObject jsonSensor;
    jsonSensor.insert("name", QString::fromStdString(s.getName()));
    jsonSensor.insert("id",int(s.getID()));
    QJsonArray jsonValues;
    for (const auto& value : s.getAllValues()) {
        jsonValues.append(value);
    }
    jsonSensor.insert("vals", jsonValues);
    jsonSensor.insert("min",float(s.getMin()));
    jsonSensor.insert("max",float(s.getMax()));
    jsonSensor.insert("type", QString::fromStdString(s.getType()));
    return jsonSensor;
}

Sensor* FileConverter::JsonObjectToSensor(const QJsonObject& obj) {
    QString type = obj["type"].toString();
    Sensor* sensor = nullptr;

    QString qname = obj["name"].toString();
    std::string name =  qname.toStdString();
    int id = obj["id"].toInt();
    float value = static_cast<float>(obj["cur"].toDouble());

    if (type == "TempSensor") {
        sensor = new TempSensor(id, qname, value);
    } else if (type == "TurbSensor") {
        sensor = new TurbSensor(id, qname, value);
    } else if (type == "PHSensor") {
        sensor = new PHSensor(id, qname, value);
    } else {
        throw std::runtime_error("Unknown sensor type");
    }

    QJsonArray jsonValues = obj["vals"].toArray();
    std::vector<float> values;
    for (const auto& value : jsonValues) {
        values.push_back(static_cast<float>(value.toDouble()));
    }
    sensor->setAllValues(values);
    sensor->setName(name);
    sensor->setMin(static_cast<float>(obj["min"].toDouble()));
    sensor->setMax(static_cast<float>(obj["max"].toDouble()));

    return sensor;
}


void FileConverter::saveJsonObjectToFile(const QString& path, const QJsonObject& obj) {
    QJsonDocument document(obj);

    QByteArray bytes = document.toJson(QJsonDocument::Indented);

    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        file.write(bytes);
        file.close();
    } else {
        throw std::runtime_error("Errore: impossibile salvare il file");
    }
}


QJsonObject FileConverter::readJsonObjectFromFile(const QString& path) {
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray bytes = file.readAll();
        file.close();

        QJsonParseError jsonError;

        QJsonDocument document = QJsonDocument::fromJson(bytes, &jsonError);

        if (jsonError.error != QJsonParseError::NoError) {
            throw std::runtime_error("Errore: impossibile leggere il file JSON");
        }

        if (document.isObject()) {
            return document.object();
        }
    } else {
        throw std::runtime_error("Errore: impossibile aprire il file per la lettura");
    }

    return QJsonObject();
}

