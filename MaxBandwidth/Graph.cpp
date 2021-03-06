
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
	clock_t start,end;
	double dur=0; 
	

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
		start = clock();
		cap.insert(verList[p->end],p->weight);
		end = clock();
		dur += (double)(end - start);
		dad[p->end]=s;
		p=p->next;
	}
	while(status[t]!=INTREE)            //4
	{
		int v = 0;
		int value = 0;

		start = clock();
		if(cap.size()<1){dad[t]=-1;return dad;}      //no such path
		v=cap.MaxMin().name.ver;
		value=cap.MaxMin().value;
		//cout<<"Find the largest finge "<<v<<" with value of "<<value<<endl;
		cap.Delete(0);
		//cap.printHeap();
		 //pick a finger with largest capacity  
		end = clock();
		dur += (double)(end - start);

		status[v]=INTREE;
		p=verList[v].head;
		while(p!=NULL)    
		{
			int w = p->end;
			if(status[w]==UNSEEN)
			{
				status[w]=FRINGE;
				dad[w]=v;
				start = clock();
				cap.insert(verList[w],min(value,p->weight));
				end = clock();
				dur += (double)(end - start);
				//cap[w]=min(cap[v],p->weight);
			}
			else if(status[w]==FRINGE && cap.Value(cap.pos[w])<p->weight)
			{
				dad[w]=v;
				start = clock();
				cap.DeletebyName(w);              //I maintain a pos[] in Heap, so this step takes O(1)
				cap.insert(verList[w],min(value,p->weight));
				end = clock();
				dur += (double)(end - start);
				//cap[w]=min(cap[v],p->weight);
			}
			p=p->next;
		}

	}
	cout<<"Heap operation in dijheap takes "<<dur*1000/CLOCKS_PER_SEC<<" ms"<<endl;
	return dad;


}
Graph* Graph::MST()
{
	clock_t start,end;
	double dur=0; 
	
	Graph *MST=new Graph(Vers);
	edgeNode *p;
	setOp e(Vers);
	Heap<edgeNode> cap(Edges*2,true);
	start = clock();

	for(int i=0;i<Vers;i++)                   //in fact every edge present twice
	{
		p=verList[i].head;
		while(p!=NULL)
		{
			cap.insert(*p,p->weight);
			p=p->next;
		}
	}  

	end = clock();
	dur += (double)(end - start);
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
		start = clock();
		int v=cap.MaxMin().name.begin;
		int w=cap.MaxMin().name.end;
		int value=cap.MaxMin().value;
		cap.Delete(0);
		end = clock();
		dur += (double)(end - start);

		int r1=e.Find(v);
		int r2=e.Find(w);
		if(r1!=r2)
		{
			//cout<<v<<"--"<<w<<": "<<value<<endl;
			//cout<<r1<<" U "<<r2<<endl;
			e.Union(r1,r2);
			//cout<<"After Uinion"<<e.Find(v)<<" U "<<e.Find(w)<<endl;
			MST->insertD(v,w);
		}
	}

	cout<<"Heap sort in MST takes "<<dur*1000/CLOCKS_PER_SEC<<" ms"<<endl;
	return MST;
}

int* Graph::Kru(int s,int t)
{
	return MST()->BFS(s,t);
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
	clock_t start,end;
	double dur=0; 
	
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

		start = clock();
		cap[p->end]=p->weight;
		end = clock();
		dur += (double)(end - start);

		dad[p->end]=s;
		p=p->next;
	}
	
	while(status[t]!=INTREE)            //4
	{
		int v = 0;
		int value = 0;
		
		start = clock();
		for(int i = 0;i<Vers;i++)
		{
			if(value<cap[i]) {v=i;value=cap[i];}  //pick a finger with largest capacity  
		}
		end = clock();
		dur += (double)(end - start);

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

				start = clock();
				cap[w]=min(cap[v],p->weight);
				end = clock();
				dur += (double)(end - start);
			}
			else if(status[w]==FRINGE && cap[w]<p->weight)
			{
				dad[w]=v;

				start = clock();
				cap[w]=min(cap[v],p->weight);
				end = clock();
				dur += (double)(end - start);
			}
			p=p->next;
		}
		cap[v]=0;

	}
	cout<<"Cap chosen in dij takes "<<dur*1000/CLOCKS_PER_SEC<<" ms"<<endl;
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
bool Graph::insertD(int u,int v,int w)
{
	verList[u].head = new edgeNode(u,v,w,verList[u].head);
	verList[v].head = new edgeNode(v,u,w,verList[v].head);
    ++Edges;
	verList[u].degree++;verList[v].degree++;
    return true;
}
void Graph::addPath(int s,int t,int max)
{
	int w;
	int v;
	int value;
	for(int i =0;i<Vers-1;i++)
	{
		w=(s+i)%Vers;
		v=(s+i+1)%Vers;
		if(v==t) {i++;continue;}
		value=rand()%max+1;
		insert(w,v,value);
		//cout<<"Add edge "<<w<<"--"<<v<<" with weight "<<value<<endl;
	}
	insert(v,t,rand()%max+1);
	//cout<<"Add edge "<<v<<"--"<<t<<" with weight "<<value<<endl;



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