#ifndef SENSORCREATOR_H
#define SENSORCREATOR_H
#include "tempsensor.h"
#include "turbsensor.h"
#include "phsensor.h"

class SensorCreator
{
public:
    TempSensor* createTemp(std::string& n) const;
    TurbSensor* createTurb(std::string& n) const;
    PHSensor* createPH(std::string& n) const;
};

#endif // SENSORCREATOR_H
