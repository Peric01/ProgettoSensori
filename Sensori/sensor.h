#ifndef SENSOR_H
#define SENSOR_H
#include <string>
#include <vector>

typedef unsigned int u_int;
class Sensor
{
protected:
    std::string Name;
    u_int SensorID;
    std::vector<float> values;
    const std::vector<int> Time = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    float MinValue = 0;
    float MaxValue = 0;
public:
    virtual ~Sensor() = default;
    Sensor(const std::string&);
    u_int getID() const;
    std::string getName() const;
    float getMin() const;
    float getMax() const;
    virtual void Simulation() const = 0;
    void addValue(float value);
    void updateMaxValue();
    void updateMinValue();
    void clearValues();
    float getCurrentValue() const;
    void removeValue(float);
    void removeLastValue();
    std::string toString() const;
    Sensor* get();
    void setID(unsigned int id);
};
#endif // SENSOR_H
