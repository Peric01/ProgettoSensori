#ifndef GRAPHBARS_H
#define GRAPHBARS_H

#include "Graph.h"

class GraphBars : public Graph
{
public:
    GraphBars();
    void setGraph(Sensor*) override;
    void setRandGraph(Sensor*) override;
};

#endif // GRAPHBARS_H
