#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include "SensorViewer.h"
#include "SimulationManager.h"
#include "SensorRepository.h"


class Controller : public QObject
{
    Q_OBJECT
private:
    bool autoMode;
    QTimer* timer;

    SensorViewer* view;
    SensorRepository* Repo;
    SimulationManager* Manager;
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    void setRepo(SensorRepository* r);
    void setManager(SimulationManager* m);
    void setView(SensorViewer* v);
    void addSensor(const QString& sensorType, unsigned int id, const QString& name, float value);
public slots:
    void save();
    void open();
    void close();
    void show() const;
    void add() const;
    void remove() const;
    void Simulation(unsigned int);
    void selectSensor() const;
    void search() const;
    void onSaveRequested();
    void onModifyRequested();
    void onDeleteRequested();
    void onSimulationRequested();
    void sensorAdded(Sensor* sensor);
};

#endif // CONTROLLER_H
