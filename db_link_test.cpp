/*
* doubly linked list 12 basic implemeentions 测试
*
* author flybird1971@gmail.com
* since  2015-05-15
*/

#pragma once

#include"stdafx.h"
#include "error_code.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "db_link_test.h"


using namespace std;

//调试 双向循环链表
void debugCircleDbList(){
	dbList db1;
	initDbList(db1);

	int length = getDbListLength(db1);
	cout << "db1 lenght : " << length << endl;
	traversal(db1);

	if (insertElementDbList(db1, 0, 12) == DOUBLY_LIST_OVERFLOW){
		cout << "下标溢出，在位置1处，插入元素12失败!!!" << endl;
	}
	else{
		cout << "插入元素成功" << endl;
	}
	cout << "遍历处理前 .... " << endl;
	traversal(db1);
	cout << "遍历处理后 .... " << endl;
	traversalDbList(db1, dealT);
	//traversal(db1);
	cout << " tail to head ... " << db1.tail->next->next->value << endl;

	//批量插入
	clock_t start = clock();
	int max = 10;
	for (int i = 0; i < max; i++){
		insertElementDbList(db1, i, i);
	}
	traversal(db1);
	cout << "length is : " << getDbListLength(db1) << endl;

	pDbNode tmpPNode = NULL;
	eleType ele;
	for (int i = max; i >= 0; i--){
		//if (delElementDbList(db1, i, ele) != OK) cout << "eroro..." << endl;
		//if (getElementDbList(db1, i, ele) != OK) cout << "eroro..." << endl;
		//ele = locateDbList(db1, i);
		//if (getPreviousDbList(db1, i, tmpPNode) != OK){
		if (getNextDbList(db1, i, tmpPNode) != OK){
			cout << "error..." << endl;
		}
		else{
			cout << "delete elememnt is " << tmpPNode->value << endl;
		}
	}

	cout << "length is : " << getDbListLength(db1) << endl;
	//traversal(db1);

	clock_t end = clock();
	long times = end - start;
	cout << "micro seconds : " << times << endl << "seconds is " << times / 1000 << endl;
	//traversal(db1);
}