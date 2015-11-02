


#ifndef _GRAPH_H_                   // include file only once
#define _GRAPH_H_



#include <iostream>
#include <ctime>
#include <cstdlib>
#include "NodeStructure.h"
#include "Heap.h"
#include "NodeStructure.h"

using namespace std;


class Graph{
public:

	Graph(int vSize);
    bool insert(int u,int v,int w=1);
    bool remove(int u,int v);
    bool exist (int u,int v) const;
	int edgewidth(int u,int v) const;
	int edges() const;
	void printVertex(int u);
	int Vdegree(int u);
	int* Dij(int s,int t);   //algorithm 1.1
	int* DijHeap(int s,int t);  //algorithm 1.2
	void printMaxWidthPath(int s,int t,int *dad);
	void empty();
    ~Graph();
private:
	bool Removedirected(int u,int v);
    int min(int x,int y);
    int Vers;
    int Edges;
    
    verNode *verList;
};

#endif