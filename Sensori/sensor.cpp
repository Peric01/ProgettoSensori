#include "sensor.h"
#include <random>
#include <algorithm>

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

void Sensor::clearValues(){
    values.clear();
}

float Sensor::getCurrentValue() const{
    if (values.empty()) {
        throw std::exception();
    }
    return values.back();
}

void Sensor::removeLastValue() {
    if (!values.empty()) {
        values.pop_back();
    }
    else
        throw std::exception();
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

Sensor* Sensor::get(){
    return this;
}

void Sensor::setID(unsigned int newId) {
    SensorID = newId;
}
