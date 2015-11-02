#ifndef _HEAP_H_                   // include file only once
#define _HEAP_H_

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Graph.h"
#include "NodeStructure.h"
using namespace std;




template <class TypeOfNode>
class Heap{
private:
	bool M;       //M: true for Maxium Heap, false for Minnum Heap
	

	HeapNode<TypeOfNode> * HeapArr;
	
	int index;
	int Size;
	bool heapfy(int num);
public:
	Heap(int s,bool maxmin=true);
	bool insert(TypeOfNode node,int value);
	HeapNode<TypeOfNode> MaxMin();        //return Max or Min Node
	bool Delete(int num);
	bool DeletebyName(int key);
	int size();
	int* pos;                  //keep positions for deleting with key easily
	void changeposition(int x,int y);
	void printHeap();
	int Value(int num);
};

template <class TypeOfNode>
Heap<TypeOfNode>::Heap(int s,bool maxmin)
{
	M=maxmin;
	Size=s;
	HeapArr = new HeapNode<TypeOfNode>[Size];
	index=0;
	pos=new int[Size]; 
	for(int i =0;i<Size;i++) pos[i]=-1;
}
template <class TypeOfNode>
int Heap<TypeOfNode>::size()
{
	return index;
}

template <class TypeOfNode>
void Heap<TypeOfNode>::changeposition(int x,int y)
{
	int ver=HeapArr[x].name.ver;
	pos[ver]=y;
	ver=HeapArr[y].name.ver;
	pos[ver]=x;
}

template <class TypeOfNode>
void Heap<TypeOfNode>::printHeap()
{
	int count=0;
	int i=0;
	cout<<"Heap is :  ";
	for(int i=0;i<index;i++)
	{
		cout<<i<<": "<<HeapArr[i].name.ver<<" ";
	}
	cout<<endl;
	cout<<"Position is :  ";
	while(count<index){
		if(pos[i]!=-1)
		{
			cout<<i<<": "<<pos[i]<<" ";
			count++;
		}
		i++;
	}
	cout<<endl;
}

template <class TypeOfNode>
bool Heap<TypeOfNode>::heapfy(int num)
{
	HeapNode<TypeOfNode> ex;
	if(num>=index) return false;
	if(M)       //Maxium heap
	{
		if(HeapArr[num].value>HeapArr[num/2].value)
		{
			
			changeposition(num,num/2);
			ex=HeapArr[num];
			HeapArr[num]=HeapArr[num/2];
			HeapArr[num/2]=ex;
			heapfy(num/2);
		}
		else if((num*2<index && HeapArr[num].value<HeapArr[num*2].value)||
			(num*2+1<index && HeapArr[num].value<HeapArr[num*2+1].value))
		{
			if(num*2+1<index && HeapArr[num*2].value<HeapArr[num*2+1].value)
			{
				changeposition(num,num*2+1);
				
				ex=HeapArr[num];
				HeapArr[num]=HeapArr[num*2+1];
				HeapArr[num*2+1]=ex;
				heapfy(num*2+1);
			}
			else
			{
				changeposition(num,num*2);
				ex=HeapArr[num];
				HeapArr[num]=HeapArr[num*2];
				HeapArr[num*2]=ex;
				heapfy(num*2);
			}
		}
	}
	else
	{
		if(HeapArr[num].value<HeapArr[num/2].value)
		{
			changeposition(num,num/2);
			ex=HeapArr[num];
			HeapArr[num]=HeapArr[num/2];
			HeapArr[num/2]=ex;
			heapfy(num/2);
		}
		else if((num*2<index && HeapArr[num].value>HeapArr[num*2].value)||
			(num*2+1<index && HeapArr[num].value>HeapArr[num*2+1].value))
		{
			if(num*2+1<index && HeapArr[num*2].value>HeapArr[num*2+1].value)
			{
				changeposition(num,num*2+1);
				ex=HeapArr[num];
				HeapArr[num]=HeapArr[num*2+1];
				HeapArr[num*2+1]=ex;
				heapfy(num*2+1);
			}
			else
			{
				changeposition(num,num*2);
				ex=HeapArr[num];
				HeapArr[num]=HeapArr[num*2];
				HeapArr[num*2]=ex;
				heapfy(num*2);
			}
		}
	}
	return true;
}


template <class TypeOfNode>
bool Heap<TypeOfNode>::insert(TypeOfNode node,int value)
{
	if(index>=Size) return false;
	HeapNode<TypeOfNode> x(node,value);
	HeapArr[index]=x;
	pos[node.ver]=index;
	index++;
	heapfy(index-1);
	return true;
}

template <class TypeOfNode>
bool Heap<TypeOfNode>::Delete(int num)
{
	
	if(num>=index) return false;
	int ver=HeapArr[num].name.ver;
	pos[ver]=-1;
	HeapArr[num]=HeapArr[index-1];
	ver=HeapArr[num].name.ver;
	pos[ver]=num;
	index--;
	heapfy(num);
	return true;
}
template <class TypeOfNode>
bool Heap<TypeOfNode>::DeletebyName(int key)
{
	int num=pos[key];
	return Delete(num);
}

template <class TypeOfNode>
int Heap<TypeOfNode>::Value(int num)   //get value by index of H[]
{
	return HeapArr[num].value;
}


template <class TypeOfNode>
HeapNode<TypeOfNode> Heap<TypeOfNode>::MaxMin()
{
	return HeapArr[0];
}



#endif