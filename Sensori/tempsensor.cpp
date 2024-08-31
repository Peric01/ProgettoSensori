#include "TempSensor.h"
#include <random>

TempSensor::TempSensor(u_int id, const QString& name,  float value) : Sensor(name.toStdString()) {
    setID(id);
    tolMin = -50;
    tolMax = 250;
    addValue(value);
    updateMinValue();
    updateMaxValue();
}

std::vector<float> TempSensor::randSimulation() const{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-50, 250);

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


bool TempSensor::validValue(float v) const{
    if(v < -50 || v > 250)
        return false;
    else
        return true;
}
