#include "sensor.h"
#include <random>

Sensor::Sensor(std::string& n) {
        Name = n;
        std::random_device rd;  // Generatore di numeri casuali hardware
        std::mt19937 gen(rd()); // Generatore Mersenne Twister inizializzato con il random device
        std::uniform_int_distribution<> dis(1, 10000); // Distribuzione uniforme tra 1 e 10000

        // Assegnazione di un ID casuale /*DA CONTROLLARE POI SE VIENE SALVATO L'ID, AL MOMENTO OGNI COMPILAZIONE NE CREA UNO NUOVO*/
        SensorID = dis(gen);
}

u_int Sensor::getID() const{
    return SensorID;
}

std::string Sensor::getName() const{
    return Name;
}
