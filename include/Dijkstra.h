#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"

class Dijkstra {

public:

    double shortestPath(
        Graph& graph,
        string start,
        string destination
    );
};

#endif