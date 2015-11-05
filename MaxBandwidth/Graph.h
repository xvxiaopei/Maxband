


#ifndef _GRAPH_H_                   // include file only once
#define _GRAPH_H_

#define VER 5000
#define MAX 5000

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "NodeStructure.h"
#include "Heap.h"
#include "NodeStructure.h"
#include "setOp.h"


using namespace std;


class Graph{
public:
	Graph(int vSize);
    bool insert(int u,int v,int w=1);      //insert edge
	bool insertD(int u,int v,int w=1);    //edges could be duplicate
    bool remove(int u,int v);             //remove edge (u-v)
    bool exist (int u,int v) const;       //return if edge(u-v) is exist
	int edgewidth(int u,int v) const;     //return the edgewidth of edge (u-v)
	int edges() const;                    //return the number of edges in this graph
	void printVertex(int u);              //print some data of the vertex v for testing
	int Vdegree(int u);                   //return the degree of u

	void addPath(int s,int t,int max=MAX);   //add a path from s to t goes through all vertices in the G
	int* Dij(int s,int t);   //algorithm 1.1
	int* DijHeap(int s,int t);  //algorithm 1.2
	int* Kru(int s,int t);     //algorithm 2
	Graph* MST();              //return MST
	int* BFS(int s,int t);     //using BFS to search a path(used in algo 2 to search the MST)
	int  printMaxWidthPath(int s,int t,int *dad);  //return width
	void empty();              //empty this graph
    ~Graph();
private:
	bool Removedirected(int u,int v);    //remove edge(u->v)
    int min(int x,int y); 
    int Vers;                            //number of vertices in this graph
    int Edges;						    // number of edges in this graph
    //edgeNode *edgeLinkList;   //keep this list for sorting(algo 2)
    verNode *verList;           //vertices list
};

#endif