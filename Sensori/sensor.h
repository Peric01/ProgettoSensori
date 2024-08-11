#ifndef SENSOR_H
#define SENSOR_H
#include <string>
#include <vector>

typedef unsigned int u_int;
class Sensor
{
protected:
    u_int SensorID;
    std::vector<float> values;
    std::string Name;
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
    //getCurrentValue per recuperare l'ultimo valore aggiunto
    //removeValue per rimuovere un valore preciso
    //removeLastValue per eliminare l'ultimo valore aggiunto
};
#endif // SENSOR_H
