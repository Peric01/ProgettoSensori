#ifndef PHSENSOR_H
#define PHSENSOR_H
#include "Sensor.h"
#include <QString>

class PHSensor : public Sensor
{
public:
    PHSensor(u_int id, const QString& name, float value);
    ~PHSensor() = default;
    void Simulation() const override;
    std::string getType() const override;
};
#endif // PHSENSOR_H
