#include "Graph.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#define VER 5000
using namespace std;

void create1(Graph * graph);

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
	
	cout<<"??"<<endl;
	Graph *g1=new Graph(VER);
	create1(g1);
	for(int i =0;i<VER;i++)
	{

			g1->printVertex(i);
			if(g1->Vdegree(i)!=6) for(;;);
		
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
				graph->insert(i,random);
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

	
