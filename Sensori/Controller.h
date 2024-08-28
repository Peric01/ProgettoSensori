#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QCoreApplication>
#include "SensorViewer.h"
#include "SimulationManager.h"
#include "SensorRepository.h"

class Controller : public QObject
{
    Q_OBJECT
private:
    bool autoMode;
    QTimer* timer;
    Sensor* selectedSensor;
    SensorViewer* view;
    SensorRepository* Repo;
    SimulationManager* Manager;
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    void setRepo(SensorRepository* r);
    void setManager(SimulationManager* m);
    void setView(SensorViewer* v);
public slots:
    void save();
    void open();
    void close();
    void add();
    void remove();
    void Simulation();
    void selectSensor();
    void pushValue();
    void popValue();
};

#endif // CONTROLLER_H
