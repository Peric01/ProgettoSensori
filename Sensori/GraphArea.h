#ifndef GRAPHAREA_H
#define GRAPHAREA_H

#include "Graph.h"

class GraphArea : public Graph
{
public:
    GraphArea();
    void setGraph(Sensor*) override;
    void setRandGraph(Sensor*) override;
};

#endif // GRAPHAREA_H
