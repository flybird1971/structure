/*
* 图
* 稀疏图，参考稀疏矩阵（三元存储，遍历整个稀疏图，获取入度为零，此次暂不处理）
*
* author flybird1971@gmail.com
* since  2015-05-24
*/
#pragma once

#include"stdafx.h"
#include "error_code.h"
#include <iostream>
#include "graph.h"
#include "queue.h"
#include "stack.h"

using namespace std;

//********************* 基本操作 ***********************
//创建 销毁
pGraph initGrap(pTriple data, unsigned size, int length){
	if (data == NULL || size < 1 || length<1) return NULL;
	void *pTmp = malloc(sizeof(graphNode)*size*size);
	if (pTmp == NULL) return NULL;

	pGraph pgraph;
	pgraph->data = (graphNode*)pTmp;
	pgraph->nodeNum = size;
	for (int i = 0; i < size; i++){
		pgraph->data[i] = 0;
	}
	
	int index = 0;
	for (int i = 0; i < length; i++){
		index = data[i].y*size + data[i].x;
		pgraph->data[index] = data[i].weight;
	}
	return pgraph;
}
pGraph initGrap(pGraph pgraph){
	if (pgraph == NULL) return NULL;
	void *pTmp = malloc(sizeof(graphNode)*pgraph->nodeNum*pgraph->nodeNum);
	if (pTmp == NULL) return NULL;

	pGraph pRes;
	pRes->data = (graphNode*)pTmp;
	pRes->nodeNum = pgraph->nodeNum;

	for (int i = 0; i < pgraph->nodeNum; i++){
		for (int k = 0; k < pgraph->nodeNum; k++){
			pRes->data[i*pgraph->nodeNum + k] = pgraph->data[i*pgraph->nodeNum + k];
		}
	}
	return pRes;
}
bool clearGrap(pGraph pgraph){
	if (pgraph == NULL) return false;
	for (int i = 0; i < pgraph->nodeNum; i++){
		for (int k = 0; k < pgraph->nodeNum; k++){
			pgraph->data[i*pgraph->nodeNum + k] = 0;
		}
	}
	return true;
}
bool destoryGraph(pGraph &pgraph){
	if (pgraph == NULL) return false;
	if (pgraph->nodeNum>0) free(pgraph->data);
	free(pgraph);
	return true;
}

//广度遍历
bool traversalBoradGraph(pGraph &pgraph, dealGraph dealF){
	if (pgraph == NULL) return false;
	void *pTmp = malloc(sizeof(int)*(pgraph->nodeNum + 1));
	if (pTmp == NULL) return false;
	int* visited = (int*)pTmp;
	int length = 0;

	int index = 0;
	queue nodeQueue;
	initQueue(nodeQueue);
	pushQueue(nodeQueue, index);
	visited[length++] = index;
	while (popQueue(nodeQueue, index) != false){
		dealF(pgraph, index);
		pushNextHopsQueue(pgraph, index, visited, length, nodeQueue);
	}
}
bool pushNextHopsQueue(pGraph pgraph,int index,int* visited,int &length,queue &nodeQueue){
	int i = 0;
	while (i++ < pgraph->nodeNum){
		if (pgraph->data[i*pgraph->nodeNum + index] < 1) continue;
		if (isVisited(visited, length, i) == true) continue;
		pushQueue(nodeQueue, i);
		visited[length++] = i;
	}
}

//深度遍历
bool traversalDepthGraph(pGraph &pgraph, dealGraph dealF){
	if (pgraph == NULL) return false;
	void *pTmp = malloc(sizeof(int)*(pgraph->nodeNum + 1));
	if (pTmp == NULL) return false;
	int* visited = (int*)pTmp;
	int length = 0;

	stack nodeStack;
	initStack(nodeStack);
	int index = 0;
	pushStack(nodeStack, index);
	visited[length++] = index;
	while (popStack(nodeStack, index) != false){
		dealF(pgraph,index);
		pushNextHopsStack(pgraph, index, visited, length, nodeStack);
	}
}
bool pushNextHopsStack(pGraph pgraph, int index, int* visited, int &length, stack &nodeStack){
	int i = 0;
	while (i++ < pgraph->nodeNum){
		if (pgraph->data[i*pgraph->nodeNum + index] < 1) continue;
		if (isVisited(visited, length, i) == true) continue;
		pushStack(nodeStack, i);
		visited[length++] = i;
	}
}

bool isVisited(int *visited, int length,int val){
	for (int k = 0; k < length; k++){
		if (visited[k] == val) return true;
	}
	return false;
}
void dealgraph(pGraph pgraph,int index){
	cout <<"values is "<< pgraph->data[index] << "\t";
}

//无向图
graphPath getMinWeight(pGraph pgraph){
	graphPath path;
	path.weight = MAX_WEIGHT;
	path.start = -1;
	path.end = -1;
	if (pgraph == NULL) return path;
	for (int i = 0; i < pgraph->nodeNum; i++){
		for (int k = 0; k < i; k++){
			if (pgraph->data[i*pgraph->nodeNum + k] < 1) continue;
			path.weight = path.weight<=pgraph->data[i*pgraph->nodeNum + k] ? pgraph->data[i*pgraph->nodeNum + k] : path.weight;
			path.start  = path.weight<=pgraph->data[i*pgraph->nodeNum + k] ? i : path.start;
			path.end    = path.weight<=pgraph->data[i*pgraph->nodeNum + k] ? k : path.end;
		}
	}
	pgraph->data[path.start*pgraph->nodeNum + path.end] = 0;
	pgraph->data[path.end*pgraph->nodeNum + path.start] = 0;
	return path;
}
pGraph productMinTreeKruskal(pGraph pgraph){
	if (pgraph == NULL) return NULL;
	pGraph pTmp = initGrap(pgraph);
	pGraph pRes = initGrap(pgraph);
	clearGrap(pRes);
	graphPath path;
	int num = 0;
	while(num<pgraph->nodeNum-1){
		path = getMinWeight(pTmp);
		pRes->data[path.start*pRes->nodeNum + path.end] = path.weight;
		pRes->data[path.end*pRes->nodeNum + path.start] = path.weight;
		if (checkCircle(pRes,path.start) == false){
			num++;
			continue;
		}
		pRes->data[path.start*pRes->nodeNum + path.end] = 0;
		pRes->data[path.end*pRes->nodeNum + path.start] = 0;
	}
	destoryGraph(pTmp);
	return pRes;
}
bool checkCircle(pGraph pgraph,int index){
	return true;
}
pGraph productMinTreePrim(pGraph pgraph){
	void *pTmp = malloc(sizeof(int)*pgraph->nodeNum);
	if (pTmp == NULL) return NULL;
	int* usedArr = (int*)pTmp;
	int usedLength = 0;
	usedArr[usedLength++] = 0;

	void *pTmp = malloc(sizeof(int)*pgraph->nodeNum);
	if (pTmp == NULL) return NULL;
	int* unusedArr = (int*)pTmp;
	int unusedLength = 0;
	for (int i = 1; i < pgraph->nodeNum; i++){
		unusedArr[unusedLength++] = 1;
	}
	pGraph pRes = initGrap(pgraph);
	clearGrap(pRes);

	graphPath path;
	while (usedLength == pgraph->nodeNum){
		path = findMinWeight(pgraph, usedArr, usedLength, unusedArr, unusedLength);
		pRes->data[path.start*pRes->nodeNum + path.end] = path.weight;
		usedArr[usedLength++] = path.end;
		unset(unusedArr, unusedLength,path.end);
	}
	return pRes;
}

graphPath findMinWeight(pGraph pgraph,int* usedArr,int usedLength,int* unusedArr,int unusedLength){
	int index;
	graphPath path;
	path.start = -1;
	path.end = -1;
	path.weight = MAX_WEIGHT;
	for (int i = 0; i < usedLength; i++){
		for (int k = 0; k < unusedLength; k++){
			index = usedArr[i]*pgraph->nodeNum + unusedArr[k];
			if (pgraph->data[index] < 1) continue;
			path.weight = path.weight > pgraph->data[index] ? pgraph->data[index] : path.weight;
			path.start = path.weight > pgraph->data[index] ? i : path.start;
			path.end = path.weight > pgraph->data[index] ? k : path.end;
		}
	}
	return path;
}

void unset(int *unusedArr, int &unusedLength,int val){
	for (int i = 0; i < unusedLength; i++){
		if (unusedArr[i] == val){
			while (i<unusedLength - 1){
				unusedArr[i] = unusedArr[i + 1];
			}
			unusedLength--;
			break;
		}
	}
}

//有向图 入度求解
bool getNodeByDegree(pGraph pgraph, int degree,stack &Stack,int director){
	if (pgraph == NULL) return false;
	int tmpDegree = 0;
	for (int i = 0; i < pgraph->nodeNum; i++){
		for (int k = 0; k < pgraph->nodeNum; k++){
			if (director == IN_DEGREE || director == IN_OUT_DEGREE){
				if (pgraph->data[k*pgraph->nodeNum + i] > 0) tmpDegree++;
			}else if (director == OUT_DEGREE || director == IN_OUT_DEGREE){
				if (pgraph->data[i*pgraph->nodeNum + k] > 0) tmpDegree++;
			}
		}
		if (tmpDegree = degree) pushStack(Stack, i);
		degree = 0;
	}
}

