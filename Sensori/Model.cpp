#include "Model.h"
#include "sensor.h"
#include <fstream>

Model::Model() {
    // Initialize the sensorCreator object
    sensorCreator = SensorCreator();
}

Model::~Model() {
    // Clear the sensors vector
    sensors.clear();
}

void Model::addSensor(std::string& type) {
    // Create a new sensor using the sensorCreator object
    Sensor* newSensor = sensorCreator.createSensor(type);

    // Add the sensor to the sensors vector
    sensors.push_back(std::move(newSensor));

    // Emit the sensorAdded signal
    emit Model::sensorAdded((sensors.back())->get());
}

void Model::removeSensor(unsigned int sensorId) {
    // Iterate over the sensors vector and find the sensor with the given sensorId
    for (auto it = sensors.begin(); it != sensors.end(); ++it) {
        if ((*it)->getID() == sensorId) {
            // Remove the sensor from the sensors vector
            sensors.erase(it);

            // Emit the sensorRemoved signal
            emit sensorRemoved(sensorId);

            break;
        }
    }
}
Sensor* Model::getSensor(unsigned int sensorId) const {
    // Iterate over the sensors vector and find the sensor with the given sensorId
    for (const auto& sensor : sensors) {
        if (sensor->getID() == sensorId) {
            return sensor->get();
        }
    }

    // If the sensor is not found, return nullptr
    return nullptr;
}

std::vector<Sensor*> Model::getAllSensors() const {
    // Create a vector to store the pointers to all sensors
    std::vector<Sensor*> allSensors;

    // Iterate over the sensors vector and add the pointers to allSensors
    for (const auto& sensor : sensors) {
        allSensors.push_back(sensor->get());
    }

    // Return the vector of all sensors
    return allSensors;
}

void Model::saveToFile(const QString& filename) const {
    // Open the file for writing
    std::ofstream file(filename.toStdString());

    // If the file is opened successfully, write the sensor data to it
    if (file.is_open()) {
        for (const auto& sensor : sensors) {
            file << sensor->toString() << std::endl;
        }

        // Close the file
        file.close();
    }
}

/*void Model::loadFromFile(const QString& filename) {
    // Open the file for reading
    std::ifstream file(filename.toStdString());

    // If the file is opened successfully, read the sensor data from it
    if (file.is_open()) {
        // Clear the sensors vector
        sensors.clear();

        // Read each line from the file
        std::string line;
        while (std::getline(file, line)) {
            // Create a new sensor using the sensorCreator object
            std::unique_ptr<Sensor> newSensor = sensorCreator.createSensorFromData(line);

            // Add the sensor to the sensors vector
            sensors.push_back(std::move(newSensor));
        }

        // Close the file
        file.close();
    }
}*/

void Model::runSimulation(unsigned int sensorId) {
    // Iterate over the sensors vector and find the sensor with the given sensorId
    for (const auto& sensor : sensors) {
        if (sensor->getID() == sensorId) {
            // Run the simulation
            sensor->Simulation();

            // Emit the simulationCompleted signal
            emit simulationCompleted(sensorId);

            break;
        }
    }
}

void Model::restartSimulation(unsigned int sensorId) {
    // Iterate over the sensors vector and find the sensor with the given sensorId
    for (const auto& sensor : sensors) {
        if (sensor->getID() == sensorId) {
            // Restart the simulation
            sensor->Simulation();

            break;
        }
    }
}

void Model::removeValue(unsigned int sensorId, size_t index) {
    // Iterate over the sensors vector and find the sensor with the given sensorId
    for (const auto& sensor : sensors) {
        if (sensor->getID() == sensorId) {
            // Remove the value at the given index
            sensor->removeValue(index);

            // Emit the sensorUpdated signal
            emit sensorUpdated(sensor->get());

            break;
        }
    }
}

void Model::clearValues(unsigned int sensorId) {
    // Iterate over the sensors vector and find the sensor with the given sensorId
    for (const auto& sensor : sensors) {
        if (sensor->getID() == sensorId) {
            // Clear all values
            sensor->clearValues();

            // Emit the dataCleared signal
            emit dataCleared(sensorId);

            break;
        }
    }
}

void Model::onSimulationRequested(unsigned int sensorId){
    // Run the simulation for the sensor with the given sensorId
    runSimulation(sensorId);
}
