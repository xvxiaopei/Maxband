#include "Graph.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#define VER 5000
#define MAX 5000
using namespace std;

void create1(Graph * graph);
void create2(Graph * graph);

int main(){
	cout<<"hello"<<endl;
	Graph x(30);
	x.insert(3,5);
	x.insert(3,7);
	x.insert(7,12);
	x.insert(12,3);
	x.printVertex(7);
	x.remove(12,7);
	x.printVertex(7);
	x.insert(12,3);
	x.printVertex(12);
	x.empty();
	x.printVertex(12);
	cout<<endl<<x.edgewidth(3,12);
	cout<<"??"<<endl;
	Graph *g1=new Graph(VER);
	Graph *g2=new Graph(VER);
	create1(g1);
	cout<<"G1 has been created."<<endl;
	create2(g2);
	cout<<"G2 has been created with ";
	cout<<g2->edges()<<" edges."<<endl;
	//for(;;);
	for(int i =0;i<VER;i++)
	{

			
			if(g2->Vdegree(i)<=800 ||g2->Vdegree(i)>=1200) 
				{
					g2->printVertex(i);
					for(;;);
			}
		
	}
	cout<<"??"<<endl;
	cout<<"??"<<endl;

}
void create1(Graph *graph)
{
	//create a graph G1 with 5000 vertices, every vertex has degree exacly 6

	srand((unsigned)time(0));
	int random;
	int count;
	int randomValue;
	for (int i = 0 ; i < VER ; i++)
	{
		count=0;
		while (graph->Vdegree(i) < 6) 
		{
				
				random = (rand() % (VER-i))+ i;    //randomly choose an end
				while(graph->Vdegree(random)>=6 || i==random)
				{
					random++;
					count++;
					if(count>VER) 
					{
						cout<<"reshuffle!!"<<endl;
						//for(;;);
						break;
					}
				}
				if(count>VER) break;
				randomValue = rand()%MAX+1;
				graph->insert(i,random,randomValue);
				//cout<<"select "<<random<<endl;
		}
		if(count>VER) break;
		//graph->printVertex(i);
	}
	if(count>VER){
		cout<<"reshuffle!!"<<endl;
		graph->empty();
		create1(graph);
	}
}


void create2(Graph *graph)
{
	//create a graph G2 with 5000 vertices, every vertex has edges going to about 20% of the other vertices
	srand((unsigned)time(0));
	int random;
	
	//int count;
	//int randomValue;
	for(int i=0; i<VER; i++)
	{
		for(int j=graph->Vdegree(i); j<VER*0.2; j++)
		{
			random = (rand() % (VER-i))+ i;
			if(graph->edges()%10000==0) cout<<graph->edges()<<" edges has been inserted." <<endl;
			if(graph->Vdegree(random) < VER*0.2)
			{
				graph->insert(i, random, rand()%MAX+1);
			}
		}
	}
	/*
	while(graph->edges() < VER * VER * 0.2/2)
	{
		random1=rand() % VER;
		//while(graph->Vdegree(random1)>VER*0.25) random1=(random1+1)%VER;
		random2=rand() % VER;
		while(random2==random1) random2=(random2+1)%VER;
		if(graph->edges()%10000==0) cout<<graph->edges() <<endl;
		graph->insert(random2,random1,rand()%MAX+1);

	}*/
}