/*
* 图
*
* author flybird1971@gmail.com
* since  2015-05-24
*/

#pragma once

#include <stdio.h>
#include <iostream>


typedef int graphNode;
const int MAX_WEIGHT	= 100000;
const int IN_DEGREE		= 1;
const int OUT_DEGREE	= 2;
const int IN_OUT_DEGREE = 3;

typedef struct graph_struct{
	graphNode * data;
	unsigned nodeNum;
}graph,*pGraph;

//带节点路径
typedef struct graph_path{
	int start;
	int end;
	int weight;
}graphPath;

//三元
typedef struct triple_data{
	int x;
	int y;
	int weight;
}triple, *pTriple;
typedef void(*dealGraph)(pGraph pgraph, int index);

//********************* 基本操作 ***********************
pGraph initGrap(pGraph pgraph);
pGraph initGrap(graphNode* data, unsigned size);
bool clearGrap(pGraph pgraph);
bool destoryGraph(pGraph &pGraph);

bool traversalBoradGraph(pGraph &pgraph, dealGraph dealF);
bool traversalDepthGraph(pGraph &pGraph, dealGraph dealF);
void dealgraph(pGraph pgraph, int index);

bool isVisited(int *visited, int length, int val);
bool pushNextHopsQueue(pGraph pgraph, int index, int* visited, int &length, queue &nodeQueue);
bool pushNextHopsStack(pGraph pgraph, int index, int* visited, int &length, stack &nodeStack);

bool checkCircle(pGraph pgraph, int index);
graphPath getMinWeight(pGraph pgraph);
pGraph productMinTreeKruskal(pGraph pgraph);
pGraph productMinTreePrim(pGraph pgraph);

graphPath findMinWeight(pGraph pgraph, int* usedArr, int usedLength, int* unusedArr, int unusedLength);
bool getNodeByDegree(pGraph pgraph, int degree, stack &Stack, int director);
void unset(int *unusedArr, int &unusedLength, int val)










