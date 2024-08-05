#include "sensorcreator.h"

TempSensor* SensorCreator::createTemp(std::string& n) const{
    return new TempSensor(n);
}

PHSensor* SensorCreator::createPH(std::string& n) const{
    return new PHSensor(n);
}

TurbSensor* SensorCreator::createTurb(std::string& n) const{
    return new TurbSensor(n);
}
