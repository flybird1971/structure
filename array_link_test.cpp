/*
* 动态数组链表 测试
*
* author flybird1971@gmail.com
* since  2015-05-15
*/
#pragma once

#include"stdafx.h"
#include "error_code.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "array_link_test.h"

using namespace std;

//调试 数组线性表
void debugArrayList(){
	SQLIST listA, listB;
	initList(listA);
	initList(listB);
	clock_t start = clock();
	for (int index = 0; index < 10 * 10; index++){
	insertElement(listA, index, index * 2);
	insertElement(listB, index, index + 2);
	}
	clock_t end = clock();
	long times = end - start;
	cout << "micro seconds : " << times << endl << "seconds is " << times / 1000 << endl;
	int k;
	getElement(listA, 1, k);
	cout << k;
	traversalList(listA);
	traversalList(listB);
}