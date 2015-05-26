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
#include "extendsEx.h"

using namespace std;

//********************* 基本操作 ***********************
//创建 销毁  参加graph_test.cpp中使用demo
pGraph initGrap(pTriple data, unsigned size, int length,bool isDirected){
	if (data == NULL || size < 1 || length<1) return NULL;
	void *pTmp = malloc(sizeof(graphNode)*size*size);
	if (pTmp == NULL) return NULL;

	void *pTmpGraph = malloc(sizeof(graph));
	if (pTmpGraph == NULL) return NULL;
	pGraph pgraph = (pGraph)pTmpGraph;
	pgraph->data = (graphNode*)pTmp;
	pgraph->nodeNum = size;
	for (int i = 0; i < size*size; i++){
		pgraph->data[i] = 0;
	}
	
	int index = 0;
	for (int i = 0; i < length; i++){
		index = data[i].y*size + data[i].x;
		pgraph->data[index] = data[i].weight;
		if (isDirected == true) continue;
		index = data[i].x*size + data[i].y;
		pgraph->data[index] = data[i].weight;
	}
	return pgraph;
}
pGraph initGrap(pGraph pgraph){
	if (pgraph == NULL) return NULL;
	void *pTmp = malloc(sizeof(graphNode)*pgraph->nodeNum*pgraph->nodeNum);
	if (pTmp == NULL) return NULL;

	void *pTmpGraph = malloc(sizeof(graph));
	if (pTmpGraph == NULL) return NULL;
	pGraph pRes = (pGraph)pTmpGraph;
	pRes->data = (graphNode*)pTmp;
	pRes->nodeNum = pgraph->nodeNum;

	int length = pgraph->nodeNum * pgraph->nodeNum;
	for (int i = 0; i < length; i++){
			pRes->data[i] = pgraph->data[i];
	}
	return pRes;
}
bool clearGrap(pGraph pgraph){
	if (pgraph == NULL) return false;
	int length = pgraph->nodeNum * pgraph->nodeNum;
	for (int i = 0; i < length; i++){
		pgraph->data[i] = 0;
	}
	return true;
}
bool destoryGraph(pGraph &pgraph){
	if (pgraph == NULL) return false;
	if (pgraph->nodeNum>0) free(pgraph->data);
	free(pgraph);
	pgraph = NULL;
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
	free(visited);
	destoryQueue(nodeQueue);
}
bool pushNextHopsQueue(pGraph pgraph, int index, int* visited, int &length, queue &nodeQueue){
	int i = 0;
	while (i < pgraph->nodeNum){
		if (pgraph->data[i*pgraph->nodeNum + index] < 1){
		}else if (isVisited(visited, length, i) == true){
		}else{
			if (pushQueue(nodeQueue, i) == false) return false;
			visited[length++] = i;
		}
		i++;
	}
	return true;
}
bool isVisited(int *visited, int length, int val){
	for (int k = 0; k < length; k++){
		if (visited[k] == val) return true;
	}
	return false;
}
void dealgraph(pGraph pgraph, int index){
	int k;
	cout << "node is " << index << "\t\tweight is ";
	for (int i = 0; i < pgraph->nodeNum; i++){
		k = index*pgraph->nodeNum + i;
		if (pgraph->data[k] > 0) cout << index << "=>" << i << "\t";
	}
	cout << endl;
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
	free(visited);
	destoryStack(nodeStack);
}
bool pushNextHopsStack(pGraph pgraph, int index, int* visited, int &length, stack &nodeStack){
	int i = 0;
	while (i < pgraph->nodeNum){
		if (pgraph->data[i*pgraph->nodeNum + index] < 1){
		}else if (isVisited(visited, length, i) == true){
		}else{
			if (pushStack(nodeStack, i) == false) return false;
			visited[length++] = i;
		}
		i++;
	}
	return false;
}

//打印矩阵
void showGraph(pGraph pgraph){
	for (int i = 0; i < pgraph->nodeNum*pgraph->nodeNum; i++){
		cout << pgraph->data[i] << "\t";
		if ((i + 1) % pgraph->nodeNum == 0) cout << endl << endl;
	}
}


//********************* 生成最小树 ***********************
//生成最小树，kruskal算法
pGraph productMinTreeKruskal(pGraph pgraph){
	if (pgraph == NULL) return NULL;
	pGraph pTmp = initGrap(pgraph);
	pGraph pRes = initGrap(pgraph);
	clearGrap(pRes);
	graphPath path;
	int num = 0;
	while (num<pgraph->nodeNum - 1){
		path = getMinWeight(pTmp);
		pRes->data[path.start*pRes->nodeNum + path.end] = path.weight;
		pRes->data[path.end*pRes->nodeNum + path.start] = path.weight;
		if (checkCircle(pRes, path.start) == true){
			num++;
			continue;
		}
		pRes->data[path.start*pRes->nodeNum + path.end] = 0;
		pRes->data[path.end*pRes->nodeNum + path.start] = 0;
	}
	destoryGraph(pTmp);
	return pRes;
}
//无向图
graphPath getMinWeight(pGraph pgraph){
	graphPath path;
	path.weight = MAX_WEIGHT_GRAPH;
	path.start = -1;
	path.end = -1;
	int index;
	if (pgraph == NULL) return path;
	for (int i = 0; i < pgraph->nodeNum; i++){
		for (int k = 0; k < i; k++){
			index = i*pgraph->nodeNum + k;
			if (pgraph->data[index] < 1) continue;
			path.start = path.weight> pgraph->data[index] ? i : path.start;
			path.end = path.weight > pgraph->data[index] ? k : path.end;
			path.weight = path.weight>pgraph->data[index] ? pgraph->data[index] : path.weight;
		}
	}
	if (path.start == -1 || path.end == -1) return path;
	pgraph->data[path.start*pgraph->nodeNum + path.end] = 0;
	pgraph->data[path.end*pgraph->nodeNum + path.start] = 0;
	return path;
}
//是否有回路
bool checkCircle(pGraph pgraph, int index){
	int  nodeNum = 0;
	int  pathNum = 0;
	bool mark;
	for (int i = 0; i < pgraph->nodeNum; i++){
		mark = false;
		for (int k = 0; k < pgraph->nodeNum; k++){
			if (pgraph->data[i*pgraph->nodeNum + k] > 0){
				pathNum++;
				mark = true;
			}
		}
		if (mark == true) nodeNum++;
	}
	return nodeNum > pathNum/2;
}

//生成最小树，prim算法
pGraph productMinTreePrim(pGraph pgraph){
	int size, usedLength, unusedLength;
	int *usedArr, *unusedArr;
	size = pgraph->nodeNum;
	createArr(size, usedArr, usedLength, unusedArr, unusedLength);
	pGraph pRes = initGrap(pgraph);
	pGraph pTmp = initGrap(pgraph);
	clearGrap(pRes);

	graphPath path;
	while (usedLength != pgraph->nodeNum){
		path = findMinWeight(pTmp, usedArr, usedLength, unusedArr, unusedLength);
		pRes->data[path.start*pRes->nodeNum + path.end] = path.weight;
		pRes->data[path.end*pRes->nodeNum + path.start] = path.weight;
		usedArr[usedLength++] = path.end;
		unset(unusedArr, unusedLength,path.end);
	}
	free(unusedArr);
	free(usedArr);
	destoryGraph(pTmp);
	return pRes;
}
graphPath findMinWeight(pGraph pgraph,int* usedArr,int usedLength,int* unusedArr,int unusedLength){
	int index;
	graphPath path;
	path.start = -1;
	path.end = -1;
	path.weight = MAX_WEIGHT_GRAPH;
	for (int i = 0; i < usedLength; i++){
		for (int k = 0; k < unusedLength; k++){
			index = usedArr[i] * pgraph->nodeNum + unusedArr[k];
			if (pgraph->data[index] < 1) continue;
			path.start = path.weight > pgraph->data[index] ? usedArr[i] : path.start;
			path.end = path.weight > pgraph->data[index] ? unusedArr[k] : path.end;
			path.weight = path.weight > pgraph->data[index] ? pgraph->data[index] : path.weight;
		}
	}
	pgraph->data[path.start*pgraph->nodeNum + path.end] = 0;
	pgraph->data[path.end*pgraph->nodeNum + path.start] = 0;
	return path;
}
void createArr(int size,int* &usedArr,int &usedLength,int* &unusedArr,int &unusedLength){
	void *pTmp = malloc(sizeof(int)*size);
	if (pTmp == NULL) return ;
	usedArr = (int*)pTmp;
	usedLength = 0;
	usedArr[usedLength++] = 0;

	pTmp = malloc(sizeof(int)*size);
	if (pTmp == NULL) return ;
	unusedArr = (int*)pTmp;
	unusedLength = 0;
	for (int i = 1; i < size; i++){
		unusedArr[unusedLength++] = i;
	}
}
void unset(int *unusedArr, int &unusedLength,int val){
	for (int i = 0; i < unusedLength; i++){
		if (unusedArr[i] == val){
			while (i<unusedLength - 1){
				unusedArr[i] = unusedArr[i+1];
				i++;
			}
			unusedLength--;
			break;
		}
	}
}



//********************* 拓扑排序 ***********************
void topologicalSort(pGraph pgraph,queue & sortQueue){
	if (pgraph == NULL) return ;
	pGraph pTmp = initGrap(pgraph);
	int i;
	stack Stack; initStack(Stack);
	while (getNodeByDegree(pTmp, 0,sortQueue, Stack, IN_DEGREE)==true){
		travservalStack(Stack);
		while (popStack(Stack, i) == true){
			pushQueue(sortQueue, i);
			clearWeigth(pTmp, i);
		}
	}
	destoryStack(Stack);
}
//将所有与index相关的路径权值置零
void clearWeigth(pGraph pgraph, int index){
	if (pgraph == NULL) return;
	for (int i = 0; i < pgraph->nodeNum; i++){
		pgraph->data[index*pgraph->nodeNum + i] = 0;
	}
}
//有向图 入度求解
bool getNodeByDegree(pGraph pgraph, int degree,queue& sortQueue,stack &Stack,int director){
	if (pgraph == NULL) return false;
	int tmpDegree = 0;
	for (int i = 0; i < pgraph->nodeNum; i++){
		if (locateQueue(sortQueue, i) == true) continue;
		for (int k = 0; k < pgraph->nodeNum; k++){
			if (director == IN_DEGREE || director == IN_OUT_DEGREE){
				if (pgraph->data[k*pgraph->nodeNum + i] > 0) tmpDegree++;
			}else if (director == OUT_DEGREE || director == IN_OUT_DEGREE){
				if (pgraph->data[i*pgraph->nodeNum + k] > 0) tmpDegree++;
			}
		}
		if (tmpDegree == degree) pushStack(Stack, i);
		tmpDegree = 0;
	}
	return getStackLength(Stack) > 0;
}

//********************* 最短路径 ***********************
void minimalApproach(pGraph pgraph,int beginPoint,int endPoint,stack& path){
	queue visited; 
	initQueue(visited);
	
	pushStack(path, beginPoint);
	pushQueue(visited,beginPoint);
	pPathNode pPath = initMinialApproach(pgraph, beginPoint);

	int tmpVal;
	int num = 0;
	while (num <pgraph->nodeNum-1 ){
		int min = getMinPath(pPath,visited,pgraph->nodeNum);
		cout << "mini " << min << endl;
		updatePathWeight(pPath, pgraph,min,beginPoint);
		cout << "after update "<<pPath[endPoint].currentNode << endl;
		getPopStack(path, tmpVal);
		if (pPath[endPoint].currentNode != tmpVal) pushStack(path, pPath[endPoint].currentNode);
		num++;
		cout << "---------------" << endl;
		travservalStack(path);
	}
	free(pPath);
	destoryQueue(visited);
	destoryStack(path);
}

void updatePathWeight(pPathNode pPath,pGraph pgraph,int min,int beginPoint){
	int newVal,val,index,next;
	int i = 0;
	while (i < pgraph->nodeNum){
		if (i == beginPoint){
			i++; continue;
		}
		index = pPath[i].currentNode * pgraph->nodeNum + min;
		next = min*pgraph->nodeNum + i;
		if (pgraph->data[index] == 0 || pgraph->data[next] == 0){
			i++; continue;
		}

		newVal = pgraph->data[index] + pgraph->data[next];
		val = pgraph->data[pPath[i].currentNode*pgraph->nodeNum + i];
		if (val == 0){
			pPath[i].currentNode = i;
			pPath[i].val = newVal;
			i++; continue;
		}
		
		pPath[i].currentNode = newVal < val ? i : pPath[i].currentNode;
		pPath[i].val = newVal < val ? pPath[i].val - val + newVal : pPath[i].val;
	}
}

//取当前最小值
int getMinPath(pPathNode pPath,queue& visited,int length){
	int min, i, pathWeight;
	i = 0;
	min = -1;
	pathWeight = MAX_WEIGHT_GRAPH;
	while (i<length){
		if (locateQueue(visited, i) == false){
			min = pathWeight>=pPath[i].val ? i : min;
			pathWeight = pathWeight>=pPath[i].val ? pPath[i].val : pathWeight;
		}
		i++;
	}
	pushQueue(visited, min);
	return min;
}

//初始化队列
pPathNode initMinialApproach(pGraph pgraph,int beginPoint){
	if (pgraph == NULL) return false;
	void *pTmp = malloc(sizeof(pathNode)*(pgraph->nodeNum));
	if (pTmp == NULL) return NULL;
	pPathNode pPath = (pPathNode)pTmp;

	int data;
	for (int i = 0; i < pgraph->nodeNum; i++){
		data = pgraph->data[beginPoint*pgraph->nodeNum + i];
		data = data < 1 ? MAX_WEIGHT_GRAPH : data;
		pPath[i].val = data;
		pPath[i].currentNode = beginPoint;
	}
	return pPath;
}


//********************* 关键路径 ***********************




