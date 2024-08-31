#include "GraphBars.h"
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>


GraphBars::GraphBars() {}

void GraphBars::setGraph(Sensor* s) {
    QBarSeries* series = new QBarSeries();
    QBarSet* set_l = new QBarSet("NCU");

    std::vector<float> vals = s->getAllValues();

    for (float it : vals) {
        set_l->append(it);
    }
    series->append(set_l);

    SimGraph = new QChart();

    QString sensorName = QString::fromStdString(s->getName());
    SimGraph->setTitle("Simulazione di: " + sensorName);

    SimGraph->addSeries(series);
    SimGraph->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    QStringList order;

    for (std::vector<float>::size_type i = 0; i < vals.size(); ++i) {
        order << QString::number(i + 1);
    }

    axisX->append(order);
    SimGraph->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(0, *std::max_element(vals.begin(), vals.end()));
    SimGraph->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}


void GraphBars::setRandGraph(Sensor* s) {
    setRandVals(s);

    QBarSeries* series = new QBarSeries();
    QBarSet* set_l = new QBarSet("NCU");

    std::vector<float> vals = getRandVals();

    for (float it : vals) {
        set_l->append(it);
    }
    series->append(set_l);

    SimGraph = new QChart();
    SimGraph->addSeries(series);
    SimGraph->setTitle("Simulazione di valori random per un sensore di torbidità");
    SimGraph->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    QStringList order;

    for (std::vector<float>::size_type i = 0; i < vals.size(); ++i) {
        order << QString::number(i + 1);
    }

    axisX->append(order);
    SimGraph->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(0, *std::max_element(vals.begin(), vals.end()));
    SimGraph->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}


