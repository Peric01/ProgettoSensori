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
