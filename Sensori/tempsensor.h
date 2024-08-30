#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H
#include "Sensor.h"
#include <QString>

class TempSensor: public Sensor
{
public:
    TempSensor(u_int id, const QString& name, float value);
    ~TempSensor() = default;
    std::vector<float> randSimulation() const override;
    std::string getType() const override;
};
#endif // TEMPSENSOR_H
