#include "sensor.h"
#include <algorithm>
#include <stdexcept>


Sensor::Sensor(const std::string& n) {
    Name = n;
}

void Sensor::addValue(float value) {
    values.push_back(value);
}

void Sensor::updateMaxValue() {
    float val = 0;
    if(!values.empty())
    {
        val = *std::max_element(values.begin(), values.end());
    }
    MaxValue = val;
}

void Sensor::updateMinValue() {
    float val = 0;
    if(!values.empty())
    {
        val = *std::min_element(values.begin(), values.end());
    }
    MinValue = val;
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

void Sensor::clearValues(){
    values.clear();
}

bool Sensor::isEmpty(){
    return values.empty();
}

float Sensor::getCurrentValue() const{
    if (values.empty()) {
        throw std::runtime_error("Il sensore non ha valori");
    }
    return values.back();
}

void Sensor::removeLastValue() {
    if (!values.empty()) {
        values.pop_back();
    }
    else
        throw std::runtime_error("Non ci sono valori da rimuovere");
}

void Sensor::removeValue(float value){
    auto it = std::find(values.begin(), values.end(), value);
    if (it != values.end()) {
        values.erase(it);
    }
}

std::string Sensor::toString() const {
    std::string result = "Sensor ID: " + std::to_string(SensorID) + "\n";
    result += "Name: " + Name + "\n";
    result += "Min Value: " + std::to_string(MinValue) + "\n";
    result += "Max Value: " + std::to_string(MaxValue) + "\n";
    result += "Values: ";
    for (const auto& value : values) {
        result += std::to_string(value) + " ";
    }
    result += "\n";
    return result;
}


void Sensor::setID(unsigned int newId) {
    SensorID = newId;
}
