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
    void setName(std::string);
    float getMin() const;
    void setMin(float);
    float getMax() const;
    void setMax(float);
    virtual std::vector<float> randSimulation() const = 0;
    void addValue(float value);
    void setAllValues(std::vector<float>);
    void updateMaxValue();
    void updateMinValue();
    void clearValues();
    float getCurrentValue() const;
    void removeValue(float);
    void removeLastValue();
    std::vector<float> getAllValues() const;
    std::string toString() const;
    void setID(unsigned int id);
    bool isEmpty();
    virtual std::string getType() const = 0;
};
#endif // SENSOR_H
