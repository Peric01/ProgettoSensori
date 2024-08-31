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
    virtual ~Graph() = 0;
    virtual void setGraph(Sensor*) = 0;
    virtual void setRandGraph(Sensor*) = 0;
    QChart* getGraph();
    void setRandVals(Sensor*);
    std::vector<float> getRandVals();
};

#endif // GRAPH_H
