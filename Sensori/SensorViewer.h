#ifndef SENSORVIEWER_H
#define SENSORVIEWER_H

#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QLineEdit>
#include <QWidgetAction>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QDialog>
#include <qfiledialog.h>
#include "Sensor.h"
class Controller;

class SensorViewer : public QWidget {
    Q_OBJECT
private:
    Controller* controller;

    // bottoni
    QPushButton* addValueButton;
    QPushButton* removeLastValueButton;
    QPushButton* runSimulationButton;

    // menù
    QAction* saveAction;
    QAction* openAction;
    QAction* closeAction;
    QAction* addAction;
    QAction* deleteAction;
    QAction* selectAction;


    // box statico ed editabile
    QVBoxLayout* staticBox;
    QVBoxLayout* editableBox;

    // liste sensori
    QVBoxLayout* temperatureLayout;
    QVBoxLayout* turbidityLayout;
    QVBoxLayout* phLayout;

    void addMenus(QVBoxLayout* mainLayout);
    void addSensors(QVBoxLayout* sensorLayout);
    void addData(QHBoxLayout* dataLayout);
    void addButtons(QVBoxLayout* buttonLayout);
    void initializeLayout(QVBoxLayout*& box, const QString& labelText);
    QFrame* addGraph();
public:
    explicit SensorViewer(QWidget* parent = nullptr);
    void showWarning(const QString&);
    QString showAddDialog();
    void showSensor(Sensor*);
    void clearLayout(QLayout*) const;
    void setController(Controller*);
    unsigned int showRemoveDialog();
    unsigned int showSelectDialog();
    unsigned int showSearchDialog();
    void clearData();
    float showValueDialog();

    void showSensorLists(std::vector<Sensor*>);
    //addDialog
    //removeDialog
};
#endif // SENSORVIEWER_H
