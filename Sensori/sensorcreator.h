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
    // serve un metodo getSensorValues per ottenere i valori da un file
};

#endif // SENSORCREATOR_H
