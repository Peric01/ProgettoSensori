#ifndef PHSENSOR_H
#define PHSENSOR_H
#include "sensor.h"

class PHSensor : public Sensor
{
private:
    std::vector<float> ph_value;
public:
    PHSensor(std::string&);
    ~PHSensor() = default;
};

#endif // PHSENSOR_H
