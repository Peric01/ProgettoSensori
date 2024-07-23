#ifndef TURBSENSOR_H
#define TURBSENSOR_H
#include "sensor.h"

class TurbSensor: public Sensor
{
private:
    std::vector<float> turb_value;
public:
    TurbSensor(std::string&);
    ~TurbSensor() = default;
};
#endif // TURBSENSOR_H
