#include "Graph.h"
#include <iostream>
using namespace std;
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
	
	cout<<"??";
}