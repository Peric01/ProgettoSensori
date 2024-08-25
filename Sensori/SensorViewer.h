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
    QFrame* info;
    Controller* controller;

    void addMenus(QVBoxLayout* mainLayout);
    void addSensors(QVBoxLayout* sensorLayout);
    void addData(QHBoxLayout* dataLayout);
    void addButtons(QVBoxLayout* buttonLayout);
    QFrame* addGraph();
public:
    explicit SensorViewer(QWidget* parent = nullptr);
    void showWarning(const QString&);
    QString showAddDialog();
    void showSensor(Sensor*);
    void clearLayout(QLayout*) const;
    void setController(Controller*);
    //addDialog
    //removeDialog
};
#endif // SENSORVIEWER_H
