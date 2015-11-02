#ifndef _SET_OP_H_                   // include file only once
#define _SET_OP_H_

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Graph.h"
#include "NodeStructure.h"
using namespace std;


class setOp{
private:
	int *dad;
	int *rank;
	int Size;
public:
	setOp(int size);
	int Find(int v);
	void Union(int w,int v);
	void MakeSet(int v);
	int *Dad();
}
;




#endif;