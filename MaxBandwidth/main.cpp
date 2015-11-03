#include "Graph.h"
#include "Heap.h"
#include "NodeStructure.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

void create1(Graph * graph);
void create2(Graph * graph);

int main(){
	
	cout<<"hello"<<endl;
	double dur;
    clock_t start,end;
    start = clock();
    Graph *g1=new Graph(VER);//dosomething
	create1(g1);
	end = clock();
    dur = (double)(end - start);
	cout<<"G1 has been created: "<<dur*1000/CLOCKS_PER_SEC<<" ms"<<endl;

	start = clock();
	int a=g1->printMaxWidthPath(200,3333,g1->Dij(200,3333));
	end = clock();
	dur = (double)(end - start);
	cout<<"Dij: "<<dur*1000/CLOCKS_PER_SEC<<" ms"<<endl;
	start = clock();
	int b=g1->printMaxWidthPath(200,3333,g1->DijHeap(200,3333));
	end = clock();
	dur = (double)(end - start);
	cout<<"DijHeap: "<<dur*1000/CLOCKS_PER_SEC<<" ms"<<endl;
	start = clock();
	int c=g1->printMaxWidthPath(200,3333,g1->Kru(200,3333));
	end = clock();
	dur = (double)(end - start);
	cout<<"Kru: "<<dur*1000/CLOCKS_PER_SEC<<" ms"<<endl;

	/*
	a=g1->printMaxWidthPath(213,2787,g1->Dij(213,2787));
	b=g1->printMaxWidthPath(213,2787,g1->DijHeap(213,2787));
	c=g1->printMaxWidthPath(213,2787,g1->Kru(213,3333));
	*/






	/*
	Graph x(8);
	x.insert(0,1,3);
	x.insert(0,5,9);
	x.insert(1,4,8);
	x.insert(1,2,17);
	x.insert(2,4,2);
	x.insert(2,3,5);
	//x.insert(3,6,1);
	//x.insert(6,4,11);
	//x.insert(6,5,6);
	x.insert(5,4,4);
	x.insert(4,7,2);
	x.insert(1,2,2);
	x.insert(3,4,15);
	x.insert(7,0,10);
	x.insert(0,6,10);
	//x.addPath(1,6,20);
	x.printVertex(4);
	x.printMaxWidthPath(1,6,x.Kru(1,6));
	x.printMaxWidthPath(1,6,x.Dij(1,6));
	x.printMaxWidthPath(1,6,x.DijHeap(1,6));
	*/
	
	
	
	/*
	Heap<verNode> m(30,false);
	verNode a,b,c,d;
	a.degree=20;
	a.ver=1;
	m.insert(a,a.degree);
	b.degree=15;
	b.ver=2;
	c.degree=19;
	c.ver=3;
	d.degree=31;
	d.ver=4;
	m.insert(b,b.degree);
	m.insert(c,c.degree);
	m.insert(d,d.degree);
	//m.Delete(0);
	m.DeletebyName(2);
	cout<<m.MaxMin().name.ver<<"  :"<<m.MaxMin().name.degree<<endl;
	m.printHeap();

	*/
	//cout<<x.Dij(3,5)[3];
	/*
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
	*/
	cout<<"??"<<endl;
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
					random=random%VER;
					count++;
					if(count>VER*3) 
					{
						//for(;;);
						break;
					}
				}
				if(count>VER*3) break;
				randomValue = rand()%MAX+1;
				graph->insert(i,random,randomValue);
				//cout<<"select "<<random<<endl;
		}
		if(count>VER*3) break;
		//graph->printVertex(i);
	}
	if(count>VER*3){
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