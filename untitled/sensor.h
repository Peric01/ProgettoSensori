#ifndef SENSOR_H
#define SENSOR_H
#include <string>

typedef unsigned int u_int;
class Sensor
{
protected:
    u_int SensorID;
    std::string Name;
    float MinValue = 0;
    float MaxValue = 0;
public:
    virtual ~Sensor() = default;
    Sensor(std::string);
    u_int getID() const;
    std::string getName() const;
    float getMin() const;
    float getMax() const;
};

#endif // SENSOR_H
