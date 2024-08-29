#include "PHSensor.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <numeric>

void PHSensor::Simulation() const{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0, 14);

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


PHSensor::PHSensor(u_int id, const QString& name, float value) : Sensor(name.toStdString()) {
    setID(id);
    addValue(value);  // Aggiunge il valore iniziale al vector values
    updateMinValue(); // Aggiorna il valore minimo
    updateMaxValue(); // Aggiorna il valore massimo
}

std::string PHSensor::getType() const {
    return "PHSensor";
}
