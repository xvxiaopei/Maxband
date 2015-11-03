#include "setOp.h"
#include <stack>

setOp::setOp(int size)
{
	Size=size;
	dad=new int[Size];
	rank=new int[Size];
}

void setOp::MakeSet(int v)
{
	dad[v]=-1;rank[v]=0;
}

int setOp::Find(int v)
{
	int w=v;
	while (dad[w]!=-1)
	{
		w=dad[w];
	}
	return w;
}
int setOp::FindC(int v)
{
	int w=v;
	stack<int> s;
	while (dad[w]!=-1)
	{
		s.push(w);
		w=dad[w];
	}
	while(!s.empty())
	{
		dad[s.top()]=w;
		s.pop();
	}

	return w;
}


void setOp::Union(int w,int v)
{
	if(rank[w]>rank[v]) dad[v]=w;
	else if(rank[w]<rank[v]) dad[w]=v;
	else
	{
		dad[v]=w;rank[w]++;
	}

}

int *setOp::Dad()
{
	return dad;
}


