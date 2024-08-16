#ifndef SENSORCREATOR_H
#define SENSORCREATOR_H
#include "tempsensor.h"
#include "turbsensor.h"
#include "phsensor.h"

class SensorCreator
{
public:
    Sensor* createSensor(std::string& t);
    TempSensor* createTemp(std::string& n) const;
    TurbSensor* createTurb(std::string& n) const;
    PHSensor* createPH(std::string& n) const;
    // serve createSensorFromData(string) per creare sensori da dei dati in un file
};

#endif // SENSORCREATOR_H
