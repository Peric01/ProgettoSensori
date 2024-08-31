#include "GraphSmoothLine.h"
#include <QSplineSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <vector>
#include <algorithm>

GraphSmoothLine::GraphSmoothLine() {}


void GraphSmoothLine::setGraph(Sensor* s) {
    std::vector<float> vals = s->getAllValues();
    QSplineSeries* series = new QSplineSeries();
    float minrange = *std::min_element(vals.begin(), vals.end());
    float maxrange = *std::max_element(vals.begin(), vals.end());

    int index = 0;
    for (float val : vals) {
        series->append(index, val);
        ++index;
    }

    SimGraph = new QChart();
    SimGraph->addSeries(series);
    QString sensorName = QString::fromStdString(s->getName());
    SimGraph->setTitle("Simulazione di: " + sensorName);
    SimGraph->legend()->hide();
    SimGraph->setVisible(true);

    // Configura l'asse X
    QValueAxis* axisX = new QValueAxis();
    axisX->setRange(0, vals.size() + 2);
    axisX->setLabelFormat("%d");
    SimGraph->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Configura l'asse Y
    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(minrange - 5, maxrange + 5);
    SimGraph->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}

void GraphSmoothLine::setRandGraph(Sensor* s){
    setRandVals(s);
    std::vector<float> vals = getRandVals();

    QSplineSeries* series = new QSplineSeries();
    float minrange = *std::min_element(vals.begin(), vals.end());
    float maxrange = *std::max_element(vals.begin(), vals.end());

    int index = 0;
    for (float val : vals) {
        series->append(index, val);
        ++index;
    }

    SimGraph = new QChart();
    SimGraph->addSeries(series);
    QString sensorName = QString::fromStdString(s->getName());
    SimGraph->setTitle("Simulazione di: " + sensorName);
    SimGraph->legend()->hide();
    SimGraph->setVisible(true);

    // Configura l'asse X
    QValueAxis* axisX = new QValueAxis();
    axisX->setRange(0, vals.size() + 2);
    axisX->setLabelFormat("%d");
    SimGraph->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Configura l'asse Y
    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(minrange - 5, maxrange + 5);
    SimGraph->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}
