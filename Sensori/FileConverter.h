#ifndef FILECONVERTER_H
#define FILECONVERTER_H

#include <QString>
#include <QJsonObject>
#include "Sensor.h"

class FileConverter
{
public:
    explicit FileConverter() = delete;
    explicit FileConverter(const FileConverter&) = delete;

    static QJsonObject SensorToJsonObject(const Sensor& s);
    static Sensor JsonObjectToColor(const QJsonObject obj);
    static void saveJSonObjectToFile(const QString& path, const QJsonObject& obj);
    static QJsonObject readJsonObjectFromFile(const QString& path);
};

#endif // FILECONVERTER_H
