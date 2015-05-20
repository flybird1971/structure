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

using namespace std;

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
void main(){

	cout << "............... start ...................... "<<endl;
	//树
	debugTree();

	//矩阵运算调试
	//debugMatrix();
	//debugSparseMatrix();

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



