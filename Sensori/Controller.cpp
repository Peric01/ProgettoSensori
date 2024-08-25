#include "Controller.h"
#include <iostream>

Controller::Controller(QObject *parent)
    : QObject(parent), autoMode(false), timer(new QTimer) {
    connect(timer,SIGNAL(timeout()),this,SLOT(show()));
}

void Controller::setRepo(SensorRepository* r) {Repo = r;}
void Controller::setManager(SimulationManager* m) {Manager = m;}
void Controller::setView(SensorViewer* v) {view = v;}

Controller::~Controller() {delete timer;}

void Controller::show(){
    Sensor* s = Repo->getSensor();
    view->showSensor(s);
}

