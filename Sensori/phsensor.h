#ifndef PHSENSOR_H
#define PHSENSOR_H
#include "sensor.h"

class PHSensor : public Sensor
{
public:
    PHSensor(const std::string&);
    ~PHSensor() = default;
    void Simulation() const override;
};
#endif // PHSENSOR_H
