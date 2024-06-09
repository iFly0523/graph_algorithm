#ifndef SHORTESTPATH_HPP
#define SHORTESTPATH_HPP
#include <limits>
#include "MinSpanTree.hpp"



void dijkstra(const unsigned int adjMat[][vexCounts], int start);

void ford(const unsigned int adjMat[][vexCounts], int start);

void Dantzig(unsigned int adjMat[][vexCounts] ,UINT start );

#endif