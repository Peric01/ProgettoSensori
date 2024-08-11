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


class SensorViewer : public QWidget
{
    Q_OBJECT
public:
    explicit SensorViewer(QWidget* parent = nullptr);
signals:

};

#endif // SENSORVIEWER_H
