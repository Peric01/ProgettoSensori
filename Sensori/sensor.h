#ifndef SENSOR_H
#define SENSOR_H
#include <string>
#include <vector>

typedef unsigned int u_int;
class Sensor
{
protected:
    u_int SensorID;
    std::string Name;
    const std::vector<int> Time = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    float MinValue = 0;
    float MaxValue = 0;
public:
    virtual ~Sensor() = default;
    Sensor(std::string&);
    virtual u_int getID() const;
    virtual std::string getName() const;
    virtual float getMin() const;
    virtual float getMax() const;
    virtual void Simulation(const Sensor*) const; /*VOID tipo da sostituire probabilmente*/
};

#endif // SENSOR_H
