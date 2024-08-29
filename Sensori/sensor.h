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
    float MinValue = 0;
    float MaxValue = 0;
public:
    virtual ~Sensor() = default;
    Sensor(const std::string&);
    u_int getID() const;
    std::string getName() const;
    float getMin() const;
    float getMax() const;
    virtual void Simulation() const;
    void addValue(float value);
    void updateMaxValue();
    void updateMinValue();
    void clearValues();
    float getCurrentValue() const;
    void removeValue(float);
    void removeLastValue();
    std::string toString() const;
    void setID(unsigned int id);
    bool isEmpty();
};
#endif // SENSOR_H
