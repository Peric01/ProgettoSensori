#ifndef PHSENSOR_H
#define PHSENSOR_H
#include "sensor.h"
#include "qstring.h"

class PHSensor : public Sensor
{
public:
    PHSensor(u_int id, const QString& name, float value);
    ~PHSensor() = default;
    void Simulation() const override;
};
#endif // PHSENSOR_H
