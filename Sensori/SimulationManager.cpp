#include "SimulationManager.h"

SimulationManager::SimulationManager() {}

SimulationManager::~SimulationManager() {}

void SimulationManager::runSimulation(Sensor* sensor) {
    if (sensor) {
        sensor->Simulation();
        emit simulationCompleted(sensor->getID());
    }
}

void SimulationManager::removeValue(Sensor* sensor, size_t index) {
    if (sensor) {
        sensor->removeValue(index);
        emit sensorUpdated(sensor);
    }
}

void SimulationManager::clearValues(Sensor* sensor) {
    if (sensor) {
        sensor->clearValues();
        emit dataCleared(sensor->getID());
    }
}

/*
    void SimulationManager::onSimulationRequested(unsigned int sensorId) {
    // Implementazione in coordinamento con SensorRepository per ottenere il sensore corretto
}
*/
