
#include "Graph.h"


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