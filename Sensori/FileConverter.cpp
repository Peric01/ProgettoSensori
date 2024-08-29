#include "FileConverter.h"
#include "tempsensor.h"
#include "phsensor.h"
#include "turbsensor.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>


QJsonObject FileConverter::SensorToJsonObject(const Sensor& s){
    QJsonObject jsonSensor;
    jsonSensor.insert("name", QString::fromStdString(s.getName())); // Conversione da std::string a QString
    jsonSensor.insert("id",int(s.getID()));
    QJsonArray jsonValues;
    for (const auto& value : s.getAllValues()) {
        jsonValues.append(value);  // Aggiungi ogni valore float al QJsonArray
    }
    jsonSensor.insert("vals", jsonValues);
    jsonSensor.insert("min",float(s.getMin()));
    jsonSensor.insert("max",float(s.getMax()));
    jsonSensor.insert("type", QString::fromStdString(s.getType()));
    return jsonSensor;
}

Sensor* FileConverter::JsonObjectToSensor(const QJsonObject& obj) {
    // Estrarre il tipo di sensore dal QJsonObject
    QString type = obj["type"].toString();

    // Creare un puntatore al sensore appropriato in base al tipo
    Sensor* sensor = nullptr;

    // Estrai i dati comuni dal QJsonObject
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

    // Popolare i valori aggiuntivi
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
    // Crea un QJsonDocument a partire dal QJsonObject
    QJsonDocument document(obj);

    // Converte il QJsonDocument in un QByteArray in formato JSON con indentazione
    QByteArray bytes = document.toJson(QJsonDocument::Indented);

    // Apre il file per la scrittura
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        // Scrivi direttamente il QByteArray nel file usando UTF-8
        file.write(bytes);
        file.close(); // Chiude il file dopo la scrittura
    } else {
        // Se l'apertura del file fallisce, lancia un'eccezione
        throw std::runtime_error("Errore: impossibile salvare il file");
    }
}


QJsonObject FileConverter::readJsonObjectFromFile(const QString& path) {
    // Apre il file per la lettura
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        // Legge tutto il contenuto del file in un QByteArray
        QByteArray bytes = file.readAll();
        file.close(); // Chiude il file dopo la lettura

        // Crea un oggetto QJsonParseError per rilevare eventuali errori durante il parsing
        QJsonParseError jsonError;

        // Crea un QJsonDocument a partire dal QByteArray
        QJsonDocument document = QJsonDocument::fromJson(bytes, &jsonError);

        // Controlla se ci sono stati errori nel parsing
        if (jsonError.error != QJsonParseError::NoError) {
            throw std::runtime_error("Errore: impossibile leggere il file JSON");
        }

        // Se il documento contiene un oggetto JSON, lo restituisce
        if (document.isObject()) {
            return document.object();
        }
    } else {
        throw std::runtime_error("Errore: impossibile aprire il file per la lettura");
    }

    // Restituisce un QJsonObject vuoto se non si riesce a leggere il file
    return QJsonObject();
}

