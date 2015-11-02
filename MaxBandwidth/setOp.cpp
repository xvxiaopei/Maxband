#include "setOp.h"

setOp::setOp(int size)
{
	Size=size;
	dad=new int[Size];
	rank=new int[Size];
}

void setOp::MakeSet(int v)
{
	dad[v]=0;rank[v]=0;
}

int setOp::Find(int v)
{
	int w=v;
	if(w>=Size){cout<<"w = "<<w;}
	while (dad[w]!=0)
	{
		w=dad[w];
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


