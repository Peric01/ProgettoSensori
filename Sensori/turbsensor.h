#ifndef TURBSENSOR_H
#define TURBSENSOR_H
#include "Sensor.h"
#include <QString>

class TurbSensor: public Sensor
{
public:
    TurbSensor(u_int id, const QString& name, float value);
    ~TurbSensor() = default;
    std::vector<float> randSimulation() const override;
    std::string getType() const override;
    bool validValue(float v) const override;
};
#endif // TURBSENSOR_H
