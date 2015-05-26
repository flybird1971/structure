/*
* ͼ����
*
* author flybird1971@gmail.com
* since  2015-05-24
*/
#pragma once

#include"stdafx.h"
#include "error_code.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "graph_test.h"

using namespace std;

//ͼ��ͨ����
void debugGraph(){
	int data[][3] = { { 1, 0, 1 }, { 2, 0, 1 }, { 3, 1, 1 }, { 3, 2, 1 }, 
					  { 6, 3, 1 }, { 5, 4, 1 }, { 4, 2, 1 }, { 5, 2, 1 }, { 5, 3, 1 }, };
	pGraph pgraph = initGrap((pTriple)data, 7, 9,false);
	showGraph(pgraph);
	//��ȱ���
	traversalBoradGraph(pgraph, dealgraph);
	
	cout << "copy graph \n";
	pGraph pgraphCopy = initGrap(pgraph);
	showGraph(pgraphCopy);
	//clearGrap(pgraphCopy);
	cout << "............... graph depth ............... \n";
	traversalDepthGraph(pgraph, dealgraph);

	destoryGraph(pgraph);
	destoryGraph(pgraphCopy);
}

//������С����ku&prim�㷨����
void debugProductTree(){
	int data[][3] = { { 1, 0, 10 }, { 2, 0, 15 }, { 3, 1, 17 }, { 3, 2, 5 },
	{ 6, 3, 20 }, { 5, 4, 6 }, { 4, 2, 3 }, { 5, 2, 1 }, { 5, 3, 9 }, };
	pGraph pgraph = initGrap((pTriple)data, 7, 9,false);
	showGraph(pgraph);
	//pGraph pRes = productMinTreeKruskal(pgraph);
	cout << "****************** min tree *****************" << endl;
	pGraph pRes = productMinTreePrim(pgraph);
	showGraph(pRes);
}

//��������
void topologicalSort(){
	int data[][3] = { { 1, 0, 10 }, { 2, 0, 15 }, { 3, 1, 17 }, { 3, 2, 5 },
	{ 6, 3, 20 }, { 5, 4, 6 }, { 4, 2, 3 }, { 5, 2, 1 }, { 5, 3, 9 }, };
	pGraph pgraph = initGrap((pTriple)data, 7, 9,true);
	showGraph(pgraph);
	queue sortQueue;
	initQueue(sortQueue);
	topologicalSort(pgraph, sortQueue);
	travservalQueue(sortQueue,fun);
}

//��С·��
void debugMinimalApproach(){
	int data[][3] = { { 1, 0, 10 }, { 2, 0, 15 }, { 3, 1, 17 }, { 3, 2, 5 },
	{ 6, 3, 20 }, { 5, 4, 6 }, { 4, 2, 3 }, { 5, 2, 1 }, { 5, 3, 9 }, };
	pGraph pgraph = initGrap((pTriple)data, 7, 9, false);
	showGraph(pgraph);
	stack path; 
	initStack(path);
	minimalApproach(pgraph,0, 6,path);
	cout << "length is " << getStackLength(path) << endl;
	travservalStack(path);//*/
}

//�ؼ�·��
void debugCriticalPath(){

}