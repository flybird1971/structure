/*
* ÅÅĞòËã·¨²âÊÔ£¨²åÈëÅÅĞò£¬Ã°ÅİÅÅĞò£¬¿ìËÙÅÅĞò£¬¶ÑÅÅĞò£¬¹é²¢ÅÅĞò£¬»ùÊıÅÅĞò£©
*
* author flybird1971@gmail.com
* since  2015-05-27
*/
#pragma once

#include"stdafx.h"
#include "error_code.h"
#include <iostream>
#include "sort_test.h"
#include "extendsEx.h"

using namespace std;

void debugInsertSort(){
	//ÕÛ°ë²éÕÒµ÷ÊÔ
	//int data[11] = { 1, 3, 3, 5, 5, 7, 8, 9, 10, 12, 20 };
	//int k = binSearch(data, 0,10,0);
	//int k = binSearchLt(data, 0, 10, 5);
	//cout << "find index : " << k << endl;
	
	//²åÈëÅÅĞòµ÷ÊÔ
	int data[11] = { 10, 8, 5, 9, 3, 12, 20, 1, 3, 5, 7 };
	printArr(data, 11, 11);
	//insertSortEx(data, 11);
	//insertSort(data, 11);
	//insertSortX(data, 11);

	//Ã°ÅİÅÅĞòµ÷ÊÔ
	bubbleSort(data, 11);
	printArr(data, 11, 11);
}
void debugQuickSort(){
	int data[11] = { 10, 8, 5, 9, 3, 12, 20, 1, 3, 5, 7 };
	printArr(data, 11, 11);
	quickSort(data, 0, 10);
	printArr(data, 11, 11);
}

void debugHeapSort();

void debugMergeSort(){
	int data[11] = { 10, 8, 5, 9, 3, 12, 20, 1, 3, 5, 7 };
	printArr(data, 11, 11);
	mergeSort(data, 0, 10);
	printArr(data, 11, 11);
}
void debugradixSort(){
	//int data[11] = { 10, 8, 5, 9, 3, 12, 20, 1, 3, 5, 7 };
	int data[11] = { 10, 80, 51,19, 23, 12, 20, 1, 30, 55, 72 };
	//printArr(data, 11, 11);
	radixSort(data, 11);
	//printArr(data, 11, 11);
}