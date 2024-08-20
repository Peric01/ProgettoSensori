#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H
#include "sensor.h"
#include "qstring.h"

class TempSensor: public Sensor
{
public:
    TempSensor(u_int id, const QString& name , float value);
    ~TempSensor() = default;
    void Simulation() const override;
};
#endif // TEMPSENSOR_H
