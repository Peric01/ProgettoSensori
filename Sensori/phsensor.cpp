#include "PHSensor.h"
#include <random>

std::vector<float> PHSensor::randSimulation() const{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.01, 14);

    std::vector<float> randValues;
    for (int i = 0; i < 12; ++i) {
        float value = dis(gen);
        randValues.push_back(value);
    }
    return randValues;
}

PHSensor::PHSensor(u_int id, const QString& name, float value) : Sensor(name.toStdString()) {
    setID(id);
    tolMin = 0.01;
    tolMax = 14;
    addValue(value);  // Aggiunge il valore iniziale al vector values
    updateMinValue(); // Aggiorna il valore minimo
    updateMaxValue(); // Aggiorna il valore massimo
}

std::string PHSensor::getType() const {
    return "PHSensor";
}

bool PHSensor::validValue(float v) const{
    if(v < 0.01 || v > 14)
        return false;
    else
        return true;
}
