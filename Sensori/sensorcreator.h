#ifndef SENSORCREATOR_H
#define SENSORCREATOR_H
#include "tempsensor.h"
#include "turbsensor.h"
#include "phsensor.h"

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
