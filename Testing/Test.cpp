#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <numeric>

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
};

class PHSensor : public Sensor
{
public:
    PHSensor(std::string&);
    ~PHSensor() = default;
    void Simulation() const override;
};

class SensorCreator
{
public:
    TempSensor* createTemp(std::string& n) const;
    TurbSensor* createTurb(std::string& n) const;
    PHSensor* createPH(std::string& n) const;
    void SensorDeleter();
};

Sensor::Sensor(const std::string& n) {
    Name = n;
    std::random_device rd;  // Generatore di numeri casuali hardware
    std::mt19937 gen(rd()); // Generatore Mersenne Twister inizializzato con il random device
    std::uniform_int_distribution<> dis(1, 10000); // Distribuzione uniforme tra 1 e 10000

    // Assegnazione di un ID casuale /*DA CONTROLLARE POI SE VIENE SALVATO L'ID, AL MOMENTO OGNI COMPILAZIONE NE CREA UNO NUOVO*/
    SensorID = dis(gen);
}

void Sensor::addValue(float value) {
    values.push_back(value);
}

void Sensor::updateMaxValue() {
    MaxValue = *std::max_element(values.begin(), values.end());
}

void Sensor::updateMinValue() {
    MinValue = *std::min_element(values.begin(), values.end());
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
    std::uniform_real_distribution<float> dis(-50, 250);

    std::vector<float> sensorValues;
    for (int i = 0; i < 12; ++i) {
        float value = dis(gen);
        sensorValues.push_back(value);
        if (i == 0) {
            std::cout << "[";
        } else {
            std::cout << ", ";
        }
        std::cout << value;
    }
    std::cout << "]" << std::endl;
    float max_value = *std::max_element(sensorValues.begin(), sensorValues.end());
    float min_value = *std::min_element(sensorValues.begin(), sensorValues.end());
    float sum = std::accumulate(sensorValues.begin(), sensorValues.end(), 0.0);
    float average = sum / sensorValues.size();
    std::cout << "Max Value: " << max_value << std::endl << "Min Value: " << min_value << std::endl;
    std::cout << "Average Value: " << average << std::endl;
}

PHSensor::PHSensor(std::string& n) : Sensor(n){}

TempSensor* SensorCreator::createTemp(std::string& n) const{
    return new TempSensor(n);
}

PHSensor* SensorCreator::createPH(std::string& n) const{
    return new PHSensor(n);
}

TurbSensor* SensorCreator::createTurb(std::string& n) const{
    return new TurbSensor(n);
}


int main(){
    std::string name = "PHSensor";
    const PHSensor ph(name);
    std::cout << "ID: " << ph.getID() << std::endl;
    std::cout << "Name: " << ph.getName() << std::endl;
    ph.Simulation();
    return 1;
}