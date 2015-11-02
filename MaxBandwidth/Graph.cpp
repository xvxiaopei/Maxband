
#include "Graph.h"
#include <queue>

Graph::Graph(int vSize)
{
	Vers=vSize;Edges=0;
    verList = new verNode[vSize];
    for(int i=0;i<Vers;++i){
		verList[i].ver = i;
		verList[i].head=NULL;
		verList[i].degree = 0;
	}
}
int Graph::min(int x,int y)
{
	return (x<y)?x:y;
}
int  Graph::printMaxWidthPath(int s,int t,int * dad)
{
	
	int ind=t;
	int value;
	if(dad[t]==-1){cout<<"No such path!"<<endl;return 0;}
	value=edgewidth(t,dad[t]);
	while(dad[ind]!=s)
	{
		cout<<ind<<" -- ";
		ind=dad[ind];
		value=min(value,edgewidth(ind,dad[ind]));
	}
	cout<<ind<<" -- ";
	ind=dad[ind];
	cout<<ind<<endl;
	cout<<"Width is "<<value<<endl;
	return value;
}

int * Graph::DijHeap(int s,int t)  //algorithm 1.2
{
	int *dad  = new int[Vers];
	edgeNode *p;
	enum STATUS{INTREE,FRINGE,UNSEEN};
	enum STATUS *status = new enum STATUS[Vers];
	Heap<verNode> cap(Vers,true);   // Maxium Heap
	for(int i=0;i<Vers;i++)             //1
	{
		status[i]=UNSEEN;
		dad[i]=-1;
	}
	status[s]=INTREE;                   //2
	p=verList[s].head;
	while(p!=NULL)    //3
	{
		status[p->end]=FRINGE;
		cap.insert(verList[p->end],p->weight);
		dad[p->end]=s;
		p=p->next;
	}
	while(status[t]!=INTREE)            //4
	{
		int v = 0;
		int value = 0;
		if(cap.size()<1){dad[t]=-1;return dad;}      //no such path
		v=cap.MaxMin().name.ver;
		value=cap.MaxMin().value;
		//cout<<"Find the largest finge "<<v<<" with value of "<<value<<endl;
		cap.Delete(0);
		//cap.printHeap();
		 //pick a finger with largest capacity  
		
		status[v]=INTREE;
		p=verList[v].head;
		while(p!=NULL)    
		{
			int w = p->end;
			if(status[w]==UNSEEN)
			{
				status[w]=FRINGE;
				dad[w]=v;
				cap.insert(verList[w],min(value,p->weight));
				//cap[w]=min(cap[v],p->weight);
			}
			else if(status[w]==FRINGE && cap.Value(cap.pos[w])<p->weight)
			{
				dad[w]=v;
				cap.DeletebyName(w);              //I maintain a pos[] in Heap, so this step takes O(1)
				cap.insert(verList[w],min(value,p->weight));
				//cap[w]=min(cap[v],p->weight);
			}
			p=p->next;
		}

	}

	return dad;


}

int* Graph::Kru(int s,int t)
{
	int *dad = new int[Vers];
	int *rank =new int[Vers];
	Graph MST(Vers);
	edgeNode *p;
	setOp e(Vers);
	Heap<edgeNode> cap(Edges*2,true);
	for(int i=0;i<Vers;i++)                   //in fact every edge present twice
	{
		p=verList[i].head;
		while(p!=NULL)
		{
			cap.insert(*p,p->weight);
			p=p->next;
		}
	}  
	/*
	while (cap.size()>0)
	{
		cout<<"Edge: "<<cap.MaxMin().name.begin<<"--"<<cap.MaxMin().name.end<<" : "<<cap.MaxMin().value<<endl;
		cap.Delete(0);
	}*/
	for(int i=0;i<Vers;i++)
	{
		e.MakeSet(i);
	}
	for(int i=0;i<Edges*2;i++)
	{
		int v=cap.MaxMin().name.begin;
		int w=cap.MaxMin().name.end;
		int value=cap.MaxMin().value;
		cap.Delete(0);
		if(e.Find(v)!=e.Find(w))
		{
			e.Union(e.Find(v),e.Find(w));
			MST.insert(v,w);
		}
	}
	
	
	return MST.BFS(s,t);
}

int * Graph::BFS(int s,int t) 
{
	int *dad= new int[Vers];
	int *dist=new int[Vers];
	int u,v;
	edgeNode *p;
	enum COLOR{White,Gray,Black};
	enum COLOR *color=new enum COLOR[Vers];
	for(int i=0;i<Vers;i++)
	{
		color[i]=White;
		dist[i]=INT_MAX;
		dad[i]=-1;
	}
	color[s]=Gray;
	dist[s]=0;
	queue<int> Q;
	Q.push(s);
	while(!Q.empty())
	{
		u=Q.front();Q.pop();
		p=verList[u].head;
		//cout<<"!!";
		while(p!=NULL)
		{
			v=p->end;
			if(color[v]==White)
			{
				color[v]=Gray;
				dad[v]=u;
				dist[v]=dist[u]+1;
				Q.push(v);
			}
			
			p=p->next;
			
		}
		color[u]=Black;
	}
	return dad;


}



int * Graph::Dij(int s,int t)    
{
	int *dad  = new int[Vers];
	edgeNode *p;
	enum STATUS{INTREE,FRINGE,UNSEEN};
	enum STATUS *status = new enum STATUS[Vers];
	int *cap= new int[Vers];
	for(int i=0;i<Vers;i++)             //1
	{
		status[i]=UNSEEN;
		dad[i]=-1;
		cap[i]=0;
	}
	status[s]=INTREE;                   //2
	p=verList[s].head;
	while(p!=NULL)    //3
	{
		status[p->end]=FRINGE;
		cap[p->end]=p->weight;
		dad[p->end]=s;
		p=p->next;
	}
	
	while(status[t]!=INTREE)            //4
	{
		int v = 0;
		int value = 0;
		for(int i = 0;i<Vers;i++)
		{
			if(value<cap[i]) {v=i;value=cap[i];}  //pick a finger with largest capacity  
		}
		if(value==0){dad[t]=-1;return dad;}      //no such path
		status[v]=INTREE;
		p=verList[v].head;
		//cout<<"Find the largest finge "<<v<<" with value of "<<value<<endl;

		while(p!=NULL)    
		{
			int w = p->end;
			if(status[w]==UNSEEN)
			{
				status[w]=FRINGE;
				dad[w]=v;
				cap[w]=min(cap[v],p->weight);
			}
			else if(status[w]==FRINGE && cap[w]<p->weight)
			{
				dad[w]=v;
				cap[w]=min(cap[v],p->weight);
			}
			p=p->next;
		}
		cap[v]=0;

	}

	return dad;
}


void Graph::empty()
{
	int i;
    edgeNode *p;
    for(i=0;i<Vers;++i){
        while((p=verList[i].head)!=NULL){
            verList[i].head=p->next;
            delete p;
        }
	}
	 for(int i=0;i<Vers;++i){
		verList[i].head=NULL;
		verList[i].degree = 0;
	}

}



Graph::~Graph()
{
    int i;
    edgeNode *p;
    for(i=0;i<Vers;++i)
        while((p=verList[i].head)!=NULL){
            verList[i].head=p->next;
            delete p;
        }
        delete [] verList;
}

bool Graph::insert(int u,int v,int w)
{
    if(exist(u,v)) return false;
	verList[u].head = new edgeNode(u,v,w,verList[u].head);
	verList[v].head = new edgeNode(v,u,w,verList[v].head);
    ++Edges;
	verList[u].degree++;verList[v].degree++;
    return true;
}


bool Graph::Removedirected(int u,int v)
{   
	edgeNode *p=verList[u].head,*q;
    if(p==NULL)return false;
    if(p->end==v)
    {
        verList[u].head = p->next;
        delete p; --Edges;
        return true;
    }
    while(p->next!=NULL&&p->next->end!=v)p=p->next;
    if(p->next==NULL)return false;
    q=p->next;p->next=q->next;delete q;
    
	verList[u].degree--;
    return true;
}

bool Graph::remove(int u,int v)
{
	if(Removedirected(u,v)) Removedirected(v,u);
	else return false;
	return true;
	--Edges;
}

int Graph::edges() const
{
	return Edges;
}
bool Graph::exist(int u,int v)const
{
    edgeNode *p=verList[u].head;
    while(p!=NULL && p->end!=v)p=p->next;
    if(p==NULL)return false;else return true;
}
int Graph::edgewidth(int u,int v) const
{
	edgeNode *p=verList[u].head;
    while(p!=NULL && p->end!=v)p=p->next;
	if(p==NULL)return 0;else return p->weight;
}

int Graph::Vdegree(int u)
{
	return verList[u].degree;
}


void Graph::printVertex(int u)
{
	cout<<"Vertex "<<u<<" has "<<Vdegree(u)<<" edges :"<<endl;
	edgeNode *p=verList[u].head;
	while(p!=NULL){
		cout<<p->end<<" with width "<<p->weight<<"   ";
		p=p->next;
	}
	cout<<endl;
}