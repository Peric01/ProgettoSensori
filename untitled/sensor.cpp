#include "sensor.h"
#include <random>

Sensor::Sensor(std::string n) {
        Sensor::Name = n;
        std::random_device rd;  // Generatore di numeri casuali hardware
        std::mt19937 gen(rd()); // Generatore Mersenne Twister inizializzato con il random device
        std::uniform_int_distribution<> dis(1, 10000); // Distribuzione uniforme tra 1 e 10000

        // Assegnazione di un ID casuale
        SensorID = dis(gen);
}

u_int Sensor::getID() const{
    return Sensor::SensorID;
}

int main(){
    std::string fammiprovare("alpaca");
    Sensor SensoreProva(fammiprovare);  // tipo nomevariabile(valori passati per la creazione)
}
