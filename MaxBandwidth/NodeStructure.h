#ifndef _NODE_H_                   // include file only once
#define _NODE_H_

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;


/*
template <typename C>
struct  HeapNode{
        C name;        //maybe node(for fringer) or edge(sorting)
		int value;        //capacity or width
		
        HeapNode(C e,int w)
        {name=e;value=w;}
    };
*/

template <class C>
struct  HeapNode{
        C name;        //maybe vertex(for fringer) or edge(for sorting)
		int value;        //capacity or width
		
        HeapNode<C>(C e,int w)
        {name=e;value=w;}
		HeapNode<C>()
		{
			name=NULL;
		}

};


struct  edgeNode{
		int begin;
        int end;
        int weight;
        edgeNode *next;
		int ver;

        edgeNode(int b=0,int e=0,int w=0,edgeNode *n=NULL)
        {begin=b;end=e;weight=w;next=n;ver=begin;}

    };

struct verNode{
        int ver;
		int degree;
        edgeNode *head;

        verNode(edgeNode *h=NULL)
        {
            head =h;
        }
    };







#endif