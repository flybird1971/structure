// stdafx.cpp : source file that includes just the standard includes
// ConsoleApplication1.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include <iostream>
//#include <string>
#include "array_link_test.h"
#include "queue_test.h"
#include "stack_test.h"
#include "db_link_test.h"
#include "maze_test.h"
#include "matrix_test.h"
#include "tree_test.h"
#include "graph_test.h"
#include "sort_test.h"

using namespace std;

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
void main(){

	cout << "............... start ...................... "<<endl;

	//算法
	//debugInsertSort();
	//debugQuickSort();
	//debugMergeSort();
	//debugradixSort();

	//图
	//debugGraph();  //图普通调试
	//debugProductTree();  //最小生成树
	//topologicalSort();     //拓扑排序
	//debugMinimalApproach(); //最小路径
	//debugCriticalPath(); //关键路径

	//树
	//debugTree();    //普通树
	//debugBTree();   //二叉树调试
	//findLeafPath(); //查找叶子路径
	//haffmanTree();  //哈弗曼树
	//haffmanEcode(); //文件压缩与解压

	//矩阵运算调试
	//debugMatrix();         //矩阵
	//debugSparseMatrix();   //稀疏矩阵调试

	//栈
	//maze();  //需要修改stack.h & stack.cpp & maze.h & maze.cpp文件
	//initHannuo(); //需要修改stack.cpp
	//dectobin();   //需要修改stack.cpp
	//debugStack(); 
	
	//队列
	//triangleDeal();
	//debugCircleQueue();
	//debugQueue();
	
	//链表
	//debugCircleDbList();
	//debugArrayList();
	int endIndefity;
	cin >> endIndefity;
}



