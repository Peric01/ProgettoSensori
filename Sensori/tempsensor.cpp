#include "TempSensor.h"
#include <random>

TempSensor::TempSensor(u_int id, const QString& name,  float value) : Sensor(name.toStdString()) {
    setID(id);
    addValue(value);  // Aggiunge il valore iniziale al vector values
    updateMinValue(); // Aggiorna il valore minimo
    updateMaxValue(); // Aggiorna il valore massimo
}

std::vector<float> TempSensor::randSimulation() const{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.01, 4000);

    std::vector<float> randValues;
    for (int i = 0; i < 12; ++i) {
        float value = dis(gen);
        randValues.push_back(value);
    }
    return randValues;
}

std::string TempSensor::getType() const{
    return "TempSensor";
}
