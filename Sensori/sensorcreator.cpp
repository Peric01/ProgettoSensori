#include "sensorcreator.h"
#include <stdexcept>
#include <sstream>

Sensor* SensorCreator::createSensorFromData(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;

    // Dividi la stringa in token basati su un delimitatore, ad esempio una virgola
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() < 2) {
        throw std::invalid_argument("Line format is incorrect");
    }

    // Assumendo che i primi due campi siano il tipo e l'ID del sensore
    std::string type = tokens[0];
    unsigned int id = std::stoul(tokens[1]);

    // Creare un sensore in base al tipo
    Sensor* sensor = createSensor(type);
    if (!sensor) {
        throw std::runtime_error("Sensor type is unknown");
    }

    // Imposta l'ID del sensore
    sensor->setID(id);

    // Imposta altri campi specifici del sensore se presenti
    // Ad esempio, se i valori successivi in `tokens` sono valori specifici del sensore:
    for (size_t i = 2; i < tokens.size(); ++i) {
        sensor->addValue(std::stof(tokens[i]));  // Ipotizzando che i valori siano float
    }

    return sensor;
}

TempSensor* SensorCreator::createTemp(std::string& n) const{
    return new TempSensor(n);
}

PHSensor* SensorCreator::createPH(std::string& n) const{
    return new PHSensor(n);
}

TurbSensor* SensorCreator::createTurb(std::string& n) const{
    return new TurbSensor(n);
}

Sensor* SensorCreator::createSensor(std::string& t){
    if (t == "temp") {
        return createTemp(t);
    } else if (t == "turb") {
        return createTurb(t);
    } else if (t == "ph") {
        return createPH(t);
    } else {
        // Handle unknown sensor type
        return nullptr;
    }
}

