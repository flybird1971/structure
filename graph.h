/*
* ͼ
*
* author flybird1971@gmail.com
* since  2015-05-24
*/

#pragma once

#include <stdio.h>
#include <iostream>
#include "queue.h"
#include "stack.h"

typedef int graphNode;
const int MAX_WEIGHT_GRAPH	= 100000;
const int IN_DEGREE			= 1;
const int OUT_DEGREE		= 2;
const int IN_OUT_DEGREE		= 3;

typedef struct graph_struct{
	graphNode * data;
	unsigned nodeNum;
}graph,*pGraph;

typedef struct path_node{
	int val;
	int currentNode;
}pathNode,*pPathNode;
//���ڵ�·��
typedef struct graph_path{
	int start;
	int end;
	int weight;
}graphPath;

//��Ԫ
typedef struct triple_data{
	int x;
	int y;
	int weight;
}triple, *pTriple;
typedef void(*dealGraph)(pGraph pgraph, int index);

//********************* �������� ***********************
pGraph initGrap(pTriple data, unsigned size, int length, bool isDirected);
pGraph initGrap(pGraph pgraph);
bool clearGrap(pGraph pgraph);
bool destoryGraph(pGraph &pGraph);

bool traversalBoradGraph(pGraph &pgraph, dealGraph dealF);
bool traversalDepthGraph(pGraph &pGraph, dealGraph dealF);
void dealgraph(pGraph pgraph, int index);

bool isVisited(int *visited, int length, int val);
bool pushNextHopsQueue(pGraph pgraph, int index, int* visited, int &length, queue &nodeQueue);
bool pushNextHopsStack(pGraph pgraph, int index, int* visited, int &length, stack &nodeStack);
void showGraph(pGraph pgraph);

//********************* ������С�� ***********************
//������С����kruskal�㷨
pGraph productMinTreeKruskal(pGraph pgraph);
graphPath getMinWeight(pGraph pgraph); //����ͼ
bool checkCircle(pGraph pgraph, int index);

//������С����prim�㷨
pGraph productMinTreePrim(pGraph pgraph);
void createArr(int size, int* &usedArr, int &usedLength, int* &unusedArr, int &unusedLength);
graphPath findMinWeight(pGraph pgraph, int* usedArr, int usedLength, int* unusedArr, int unusedLength);
void unset(int *unusedArr, int &unusedLength, int val);


//********************* �������� ***********************
void topologicalSort(pGraph pgraph, queue & sortQueue);
void clearWeigth(pGraph pgraph, int index);
bool getNodeByDegree(pGraph pgraph, int degree, queue& sortQueue, stack &Stack, int director); //����ͼ ������


//********************* ���·�� ***********************
void minimalApproach(pGraph pgraph, int beginPoint, int endPoint, stack& path);
void updatePathWeight(pPathNode pPath, pGraph pgraph, int min, int beginPoint);
int getMinPath(pPathNode pPath, queue& visited, int length);
pPathNode initMinialApproach(pGraph pgraph, int beginPoint);


//********************* �ؼ�·�� ***********************











