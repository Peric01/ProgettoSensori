#include "GraphArea.h"

#include <QLineSeries>
#include <QAreaSeries>
#include <QValueAxis>

GraphArea::GraphArea() {}


void GraphArea::setGraph(Sensor* s) {
    std::vector<float> vals = s->getAllValues();

    QLineSeries *sensorSeries = new QLineSeries();
    QLineSeries *referenceSeries = new QLineSeries();
    int index = 0;
    for (float val : vals) {
        sensorSeries->append(index, val);
        referenceSeries->append(index, 7); // Valore neutro di pH
        ++index;
    }
    referenceSeries->setColor(Qt::black);

    QAreaSeries *areaBelow = new QAreaSeries(referenceSeries, sensorSeries);
    QAreaSeries *areaAbove = new QAreaSeries(sensorSeries, referenceSeries);

    QColor grayColor(128, 128, 128, 100);
    areaBelow->setBrush(QBrush(grayColor));
    areaAbove->setBrush(QBrush(grayColor));
    SimGraph = new QChart();
    SimGraph->addSeries(areaAbove);
    SimGraph->addSeries(areaBelow);
    SimGraph->addSeries(sensorSeries);
    SimGraph->addSeries(referenceSeries);


    QString sensorName = QString::fromStdString(s->getName());
    SimGraph->setTitle("Valori del Sensore di pH: " + sensorName);
    SimGraph->legend()->hide();

    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, vals.size() - 1);
    axisX->setLabelFormat("%d");
    axisX->setGridLineVisible(true);
    axisX->setTickCount(vals.size());
    SimGraph->addAxis(axisX, Qt::AlignBottom);
    sensorSeries->attachAxis(axisX);
    referenceSeries->attachAxis(axisX);

    float minVal = *std::min_element(vals.begin(), vals.end());
    float maxVal = *std::max_element(vals.begin(), vals.end());
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(std::min(minVal, 0.0f), std::max(maxVal, 14.0f));
    axisY->setLabelFormat("%0.1f");
    axisY->setGridLineVisible(true);
    axisY->setTickCount(10);
    SimGraph->addAxis(axisY, Qt::AlignLeft);
    sensorSeries->attachAxis(axisY);
    referenceSeries->attachAxis(axisY);
    SimGraph->setVisible(true);
}


void GraphArea::setRandGraph(Sensor* s){
    setRandVals(s);
    std::vector<float> vals = getRandVals();
    QLineSeries *sensorSeries = new QLineSeries();
    QLineSeries *referenceSeries = new QLineSeries();
    int index = 0;
    for (float val : vals) {
        sensorSeries->append(index, val);
        referenceSeries->append(index, 7); // Valore neutro di pH
        ++index;
    }
    referenceSeries->setColor(Qt::black);

    QAreaSeries *areaBelow = new QAreaSeries(referenceSeries, sensorSeries);
    QAreaSeries *areaAbove = new QAreaSeries(sensorSeries, referenceSeries);

    QColor grayColor(128, 128, 128, 100);
    areaBelow->setBrush(QBrush(grayColor));
    areaAbove->setBrush(QBrush(grayColor));
    SimGraph = new QChart();
    SimGraph->addSeries(areaAbove);
    SimGraph->addSeries(areaBelow);
    SimGraph->addSeries(sensorSeries);
    SimGraph->addSeries(referenceSeries);


    QString sensorName = QString::fromStdString(s->getName());
    SimGraph->setTitle("Valori del Sensore di pH: " + sensorName);
    SimGraph->legend()->hide();

    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, vals.size() - 1);
    axisX->setLabelFormat("%d");
    axisX->setGridLineVisible(true);
    axisX->setTickCount(vals.size());
    SimGraph->addAxis(axisX, Qt::AlignBottom);
    sensorSeries->attachAxis(axisX);
    referenceSeries->attachAxis(axisX);

    float minVal = *std::min_element(vals.begin(), vals.end());
    float maxVal = *std::max_element(vals.begin(), vals.end());
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(std::min(minVal, 0.0f), std::max(maxVal, 14.0f));
    axisY->setLabelFormat("%0.1f");
    axisY->setGridLineVisible(true);
    axisY->setTickCount(10);
    SimGraph->addAxis(axisY, Qt::AlignLeft);
    sensorSeries->attachAxis(axisY);
    referenceSeries->attachAxis(axisY);
    SimGraph->setVisible(true);
}
