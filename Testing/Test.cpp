#include "Model.h"
#include <fstream>

Model::Model() {
    // Constructor implementation
}

Model::~Model() {
    // Destructor implementation
}

void Model::addSensor(const std::string& type, const std::string& name) {
    // Create a new sensor using the SensorCreator
    std::unique_ptr<Sensor> newSensor = sensorCreator.createSensor(type, name);
    
    // Add the sensor to the vector
    sensors.push_back(std::move(newSensor));
    
    // Emit the signal to notify observers
    emit sensorAdded(sensors.back().get());
}

void Model::removeSensor(unsigned int sensorId) {
    // Find the sensor with the given ID
    auto it = std::find_if(sensors.begin(), sensors.end(), [sensorId](const std::unique_ptr<Sensor>& sensor) {
        return sensor->getId() == sensorId;
    });
    
    if (it != sensors.end()) {
        // Remove the sensor from the vector
        sensors.erase(it);
        
        // Emit the signal to notify observers
        emit sensorRemoved(sensorId);
    }
}

Sensor* Model::getSensor(unsigned int sensorId) const {
    // Find the sensor with the given ID
    auto it = std::find_if(sensors.begin(), sensors.end(), [sensorId](const std::unique_ptr<Sensor>& sensor) {
        return sensor->getId() == sensorId;
    });
    
    if (it != sensors.end()) {
        // Return a pointer to the sensor
        return it->get();
    }
    
    return nullptr;
}

std::vector<Sensor*> Model::getAllSensors() const {
    std::vector<Sensor*> allSensors;
    
    // Iterate over all sensors and add them to the result vector
    for (const auto& sensor : sensors) {
        allSensors.push_back(sensor.get());
    }
    
    return allSensors;
}

void Model::saveToFile(const QString& filename) const {
    std::ofstream file(filename.toStdString());
    
    if (file.is_open()) {
        // Write the sensor data to the file
        for (const auto& sensor : sensors) {
            file << sensor->toString() << std::endl;
        }
        
        file.close();
    }
}

void Model::loadFromFile(const QString& filename) {
    std::ifstream file(filename.toStdString());
    
    if (file.is_open()) {
        // Clear the existing sensors
        sensors.clear();
        
        // Read the sensor data from the file and create new sensors
        std::string line;
        while (std::getline(file, line)) {
            // Parse the line and create a new sensor
            std::unique_ptr<Sensor> newSensor = sensorCreator.createSensorFromLine(line);
            
            // Add the sensor to the vector
            sensors.push_back(std::move(newSensor));
        }
        
        file.close();
    }
}

void Model::runSimulation(unsigned int sensorId, int numDataPoints) {
    // Find the sensor with the given ID
    Sensor* sensor = getSensor(sensorId);
    
    if (sensor) {
        // Run the simulation on the sensor
        sensor->runSimulation(numDataPoints);
        
        // Emit the signal to notify observers
        emit simulationCompleted(sensorId);
    }
}

void Model::restartSimulation(unsigned int sensorId) {
    // Find the sensor with the given ID
    Sensor* sensor = getSensor(sensorId);
    
    if (sensor) {
        // Restart the simulation on the sensor
        sensor->restartSimulation();
        
        // Emit the signal to notify observers
        emit simulationCompleted(sensorId);
    }
}

void Model::removeValue(unsigned int sensorId, size_t index) {
    // Find the sensor with the given ID
    Sensor* sensor = getSensor(sensorId);
    
    if (sensor) {
        // Remove the value at the specified index
        sensor->removeValue(index);
        
        // Emit the signal to notify observers
        emit sensorUpdated(sensor);
    }
}

void Model::clearValues(unsigned int sensorId) {
    // Find the sensor with the given ID
    Sensor* sensor = getSensor(sensorId);
    
    if (sensor) {
        // Clear all values of the sensor
        sensor->clearValues();
        
        // Emit the signal to notify observers
        emit dataCleared(sensorId);
    }
}

void Model::onSimulationRequested(unsigned int sensorId, int numDataPoints) {
    // This slot is connected to the signal emitted by the UI when a simulation is requested
    runSimulation(sensorId, numDataPoints);
}
