#include "turbsensor.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <numeric>

TurbSensor::TurbSensor(std::string& n) : Sensor(n){}

void TurbSensor::Simulation() const{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.01, 4000);

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
