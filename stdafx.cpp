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
	//��
	debugTree();

	//�����������
	//debugMatrix();
	//debugSparseMatrix();

	//ջ
	//maze();  //��Ҫ�޸�stack.h & stack.cpp & maze.h & maze.cpp�ļ�
	//initHannuo(); //��Ҫ�޸�stack.cpp
	//dectobin();   //��Ҫ�޸�stack.cpp
	//debugStack(); 
	
	//����
	//triangleDeal();
	//debugCircleQueue();
	//debugQueue();
	
	//����
	//debugCircleDbList();
	//debugArrayList();
	int endIndefity;
	cin >> endIndefity;
}



