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


class SensorViewer : public QWidget {
    Q_OBJECT
private:
    void addMenus(QVBoxLayout* mainLayout);
    void addSensors(QVBoxLayout* sensorLayout);
    void addData(QHBoxLayout* dataLayout);    // Modifica qui: QVBoxLayout invece di QHBoxLayout
    void addButtons(QVBoxLayout* buttonLayout); // Modifica qui: QVBoxLayout invece di (QSpacerItem*, QSpacerItem*, QVBoxLayout*)
    QFrame* addGraph();
public:
    explicit SensorViewer(QWidget* parent = nullptr);
    void showWarning(const QString&);
    QString showAddDialog();
};
#endif // SENSORVIEWER_H
