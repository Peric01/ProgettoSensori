#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

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
    virtual void updateMaxValue() = 0;
    virtual void updateMinValue() = 0;
};

class PHSensor : public Sensor
{
public:
    PHSensor(std::string&);
    ~PHSensor() = default;
    void Simulation() const override;
    void addValue(float value);
    void updateMaxValue() override;
    void updateMinValue() override;
};

Sensor::Sensor(const std::string& n) {
    Name = n;
    std::random_device rd;  // Generatore di numeri casuali hardware
    std::mt19937 gen(rd()); // Generatore Mersenne Twister inizializzato con il random device
    std::uniform_int_distribution<> dis(1, 10000); // Distribuzione uniforme tra 1 e 10000

    // Assegnazione di un ID casuale /*DA CONTROLLARE POI SE VIENE SALVATO L'ID, AL MOMENTO OGNI COMPILAZIONE NE CREA UNO NUOVO*/
    SensorID = dis(gen);
}

u_int Sensor::getID() const{
    return SensorID;
}

std::string Sensor::getName() const{
    return Name;
}

float Sensor::getMin() const{
    return MinValue;
}

float Sensor::getMax() const{
    return MaxValue;
}

void PHSensor::Simulation() const{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0, 14);

    std::vector<float> sensorValues;
    
    for (int i = 0; i < Time.size(); i++) {
        float value = dis(gen);
        sensorValues.push_back(value);
        if (i == 0) {
            std::cout << "[";
            std::cout << value;
        }
        std::cout << ", " << value;
        if (i == Time.size() - 1)
            std::cout << "]" << std::endl;
    }
    float max_value = *std::max_element(sensorValues.begin(), sensorValues.end());
    float min_value = *std::min_element(sensorValues.begin(), sensorValues.end());
    float sum = std::accumulate(sensorValues.begin(), sensorValues.end(), 0.0);
    float average = sum / sensorValues.size();
    std::cout << "Max Value: " << max_value << std::endl << "Min Value: " << min_value << std::endl;
    std::cout << "Average Value: " << average << std::endl;
}

PHSensor::PHSensor(std::string& n) : Sensor(n){}

void PHSensor::addValue(float value) {
    values.push_back(value);
}

void PHSensor::updateMaxValue() {
    MaxValue = *std::max_element(values.begin(), values.end());
}

void PHSensor::updateMinValue() {
    MinValue = *std::min_element(values.begin(), values.end());
}

int main(){
    std::string name = "PHSensor";
    const PHSensor ph(name);
    std::cout << "ID: " << ph.getID() << std::endl;
    std::cout << "Name: " << ph.getName() << std::endl;
    ph.Simulation();
    return 0;
}