#ifndef SENSORCREATOR_H
#define SENSORCREATOR_H
#include "TempSensor.h"
#include "TurbSensor.h"
#include "PHSensor.h"

class SensorCreator
{
public:
    Sensor* createSensor(const std::string& t) const;
    TempSensor* createTemp(const QString& n) const;
    TurbSensor* createTurb(const QString& n) const;
    PHSensor* createPH(const QString& n) const;
    Sensor* createSensorFromData(const std::string& line);
};

#endif // SENSORCREATOR_H
