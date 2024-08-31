#include "SensorCreator.h"
#include <stdexcept>
#include <sstream>

Sensor* SensorCreator::createSensorFromData(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() < 2) {
        throw std::invalid_argument("Line format is incorrect");
    }

    std::string type = tokens[0];
    unsigned int id = std::stoul(tokens[1]);

    Sensor* sensor = createSensor(type);
    if (!sensor) {
        throw std::runtime_error("Sensor type is unknown");
    }

    sensor->setID(id);

    for (size_t i = 2; i < tokens.size(); ++i) {
        sensor->addValue(std::stof(tokens[i]));
    }

    return sensor;
}


PHSensor* SensorCreator::createPH(const QString& n) const {
    u_int id = 1;
    float value = 0.0;
    return new PHSensor(id, n, value);
}

TurbSensor* SensorCreator::createTurb(const QString& n) const {
    u_int id = 1;
    float value = 0.0;
    return new TurbSensor(id, n, value);
}

TempSensor* SensorCreator::createTemp(const QString& n) const {
    u_int id = 1;
    float value = 0.0;
    return new TempSensor(id, n, value);
}

Sensor* SensorCreator::createSensor(const std::string& t) const {
    if (t == "temp") {
        return createTemp("DefaultName");
    } else if (t == "turb") {
        return createTurb("DefaultName");
    } else if (t == "ph") {
        return createPH("DefaultName");
    } else {
        return nullptr;
    }
}
