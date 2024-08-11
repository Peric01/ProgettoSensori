#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H
#include "sensor.h"

class TempSensor: public Sensor
{
public:
    TempSensor(std::string&);
    ~TempSensor() = default;
    void Simulation() const override;
};
#endif // TEMPSENSOR_H
