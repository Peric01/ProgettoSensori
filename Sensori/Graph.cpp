#include "Graph.h"

Graph::Graph() {}

QChart* Graph::getGraph(){
    return SimGraph;
}

void Graph::setRandVals(Sensor* s){
    RandVals =  s->randSimulation();
}

std::vector<float> Graph::getRandVals(){
    return RandVals;
}
