#include "TurbSensor.h"
#include <random>

TurbSensor::TurbSensor(u_int id, const QString& name, float value) : Sensor(name.toStdString()) {
    setID(id);
    tolMin = 0.01;
    tolMax = 4000;
    addValue(value);
    updateMinValue();
    updateMaxValue();
}

std::vector<float> TurbSensor::randSimulation() const{
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

std::string TurbSensor::getType() const{
    return "TurbSensor";
}

bool TurbSensor::validValue(float v) const{
    if(v < 0.01 || v > 4000)
        return false;
    else
        return true;
}
