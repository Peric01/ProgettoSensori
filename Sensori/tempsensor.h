#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H
#include "sensor.h"

class TempSensor: public Sensor
{
private:
    std::vector<float> temp_value;
public:
    TempSensor(std::string&);
    ~TempSensor() = default;
};
#endif // TEMPSENSOR_H
