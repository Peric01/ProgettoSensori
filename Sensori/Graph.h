#ifndef GRAPH_H
#define GRAPH_H

#include <QChart>
#include "Sensor.h"
#include <vector>

class Graph
{
protected:
    QChart* SimGraph;
    std::vector<float> RandVals;
public:
    Graph();
    virtual void setGraph(Sensor*) = 0;
    virtual void setRandGraph(Sensor*) = 0; // deve svuotare l'array creato il grafico
    QChart* getGraph();
    void setRandVals(Sensor*);
    std::vector<float> getRandVals();
};

#endif // GRAPH_H
