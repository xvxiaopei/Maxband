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
	bool M;       //M: ture for Maxium Heap, false for Minnum Heap
	

	HeapNode<TypeOfNode> * HeapArr;
	int index;
	int Size;
	bool heapfy(int num);
public:
	Heap(int size,bool maxmin=true);
	bool insert(TypeOfNode node,int value);
	TypeOfNode MaxMin();        //return Max or Min Node
	bool Delete(int num);

};

template <class TypeOfNode>
Heap<TypeOfNode>::Heap(int size,bool maxmin)
{
	M=maxmin;
	Size=size;
	HeapArr = new HeapNode<TypeOfNode>[Size];
	index=0;
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
				ex=HeapArr[num];
				HeapArr[num]=HeapArr[num*2+1];
				HeapArr[num*2+1]=ex;
				heapfy(num*2+1);
			}
			else
			{
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
				ex=HeapArr[num];
				HeapArr[num]=HeapArr[num*2+1];
				HeapArr[num*2+1]=ex;
				heapfy(num*2+1);
			}
			else
			{
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
	index++;
	heapfy(index-1);
	return true;
}

template <class TypeOfNode>
bool Heap<TypeOfNode>::Delete(int num)
{
	if(num>=index) return false;
	HeapArr[num]=HeapArr[index-1];
	index--;
	heapfy(num);
	return true;
}


template <class TypeOfNode>
TypeOfNode Heap<TypeOfNode>::MaxMin()
{
	return HeapArr[0].name;
}



#endif