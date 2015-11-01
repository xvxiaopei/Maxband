


#ifndef _GRAPH_H_                   // include file only once
#define _GRAPH_H_

#include <iostream>
#include <ctime>
#include <cstdlib>

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
	void empty();
    ~Graph();
private:
	bool Removedirected(int u,int v);
    struct  edgeNode{
        int end;
        int weight;
        edgeNode *next;

        edgeNode(int e,int w,edgeNode *n=NULL)
        {end=e;weight=w;next=n;}

    };
    int Vers;
    int Edges;
    struct verNode{
        int ver;
		int degree;
        edgeNode *head;

        verNode(edgeNode *h=NULL)
        {
            head =h;
        }
    };
    verNode *verList;
};

#endif