#ifndef TURBSENSOR_H
#define TURBSENSOR_H
#include "sensor.h"

class TurbSensor: public Sensor
{
public:
    TurbSensor(std::string&);
    ~TurbSensor() = default;
    void Simulation() const override;
};
#endif // TURBSENSOR_H
