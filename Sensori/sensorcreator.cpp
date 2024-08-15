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

Sensor* SensorCreator::createSensor(std::string& t){
    if (t == "temp") {
        return createTemp(t);
    } else if (t == "turb") {
        return createTurb(t);
    } else if (t == "ph") {
        return createPH(t);
    } else {
        // Handle unknown sensor type
        return nullptr;
    }
}

