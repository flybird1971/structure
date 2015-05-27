/*
* 帮助中心，常用函数放于此处
*
* author flybird1971@gmail.com
* since  2015-05-25
*/
#pragma once

#include"stdafx.h"
#include <stdio.h>
#include <iostream>
#include "extendsEx.h"

using namespace std;

//打印数组
void printArr(int* arr, int size, int lineNum){
	if (size < 1 || arr == NULL) return;
	for (int i = 0; i < size; i++){
		cout << arr[i] << "\t";
		if (lineNum>1 && (i + 1) % lineNum == 0) cout << endl;
	}
}

//开辟内存，模拟数组
void* createArrByType(int type,int size){
	if (size < 1) return NULL;
	int sizeMem = 0;
	switch (type){
		case  CHAR_TYPE:
			sizeMem = sizeof(char)*size;
			break;
		case  INT_TYPE:
			sizeMem = sizeof(int)*size;
			break;
		default:
			sizeMem = size;
			break;
	}
	void *tmp = malloc(sizeMem);
	return tmp;
}

void initArr(int* data,int lenght, int defaultVal){
	for (int i = 0; i < lenght; i++){
		data[i] = defaultVal;
	}
}
