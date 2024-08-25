#ifndef TURBSENSOR_H
#define TURBSENSOR_H
#include "sensor.h"
#include <QString>

class TurbSensor: public Sensor
{
public:
    TurbSensor(u_int id, const QString& name, float value);
    ~TurbSensor() = default;
    void Simulation() const override;
};
#endif // TURBSENSOR_H
