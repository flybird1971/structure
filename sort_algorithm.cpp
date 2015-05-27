/*
* 排序算法（插入排序，冒泡排序，快速排序，堆排序，归并排序，基数排序）
*
* author flybird1971@gmail.com
* since  2015-05-27
*/
#pragma once

#include"stdafx.h"
#include "error_code.h"
#include <iostream>
#include "sort_algorithm.h"
#include "extendsEx.h"

using namespace std;

//************************** 折半查找 *****************************************//
/*
* 折半查找 小于val ,返回第一个比他大的下标，
* 若果都小于 val ,返回end+1
*/
int binSearchLt(int* data, int begin, int end, int val){
	if (data[end] <= val) return end + 1;
	if (data[begin]>val) return begin;
	if (end - begin == 1) return begin + 1;
	int med = (end + begin) / 2;
	if (data[med] > val) end = med;
	if (data[med] <= val) begin = med;
	//cout << "med is " << med << "\tbegin is " << begin << "\tend is " << end << endl;
	return binSearchLt(data, begin, end, val);
}

//折半查找 等于val
int binSearch(int* data, int begin, int end, int val){
	if (data[end] < val || data[begin]>val) return -1;
	if (end - begin == 1){
		if (data[begin] == val) return begin;
		if (data[end] == val) return end;
		return -1;
	}
	int med = (end + begin) / 2;
	if (data[med] > val) end = med;
	if (data[med] < val) begin = med;
	if (data[med] == val) return med;
	return binSearch(data, begin, end, val);
}


//************************** 插入排序 *****************************************//
//插入排序
void insertSort(int* data, int length){
	int k,tmpData;
	for (int i = 1; i < length; i++){
		k = i - 1;
		while (k>=0 && data[k]>data[i]){ 
			k--; 
		}
		tmpData = data[i];
		while (i-1 > k){
			data[i] = data[i-1];
			i--;
		}
		data[i] = tmpData;
	}
}
//插入排序增强版，使用折半查找继续快速比较
void insertSortX(int* data, int length){
	int k, tmpData;
	for (int i = 1; i < length; i++){
		k = binSearchLt(data, 0, i-1, data[i]);
		tmpData = data[i];
		while (i > k){
			data[i] = data[i-1];
			i--;
		}
		data[i] = tmpData;
	}
}
//直接交换值
void insertSortEx(int* data, int length){
	int k, tmpData;
	for (int i = 1; i < length; i++){
		k = i - 1;
		while (k >= 0 && data[k + 1] < data[k]){
			tmpData = data[k + 1];
			data[k + 1] = data[k];
			data[k] = tmpData;
			k--;
		}
	}
}

//************************** 冒泡排序 *****************************************//
void bubbleSort(int* data, int length){
	int tmpVal;
	bool mark = false;
	int time = length-1;
	for (int k = 0; k < length-1; k++){
		for (int i = 0; i < time; i++){
			if (data[i + 1] < data[i]){
				mark = true;
				tmpVal = data[i + 1];
				data[i + 1] = data[i];
				data[i] = tmpVal;
			}
		}
		if (mark == false) break;
		mark = false;
		time--;
	}
}

//************************** 快速排序 *****************************************//
bool quickSort(int* data,int begin,int end){
	if (end <= begin) return true; //return 条件
	int med = deuce(data, begin, end); //parme

	quickSort(data,begin, med-1); //左 quickSort();
	quickSort(data,med+1, end);//右quickSort();
	return true;
}
int deuce(int* data,int begin,int end){
	int val = data[end];
	int front = begin;
	int rear = end;
	int director = 0;
	while (front != rear){
		switch (director){
			case 0 :
				if (data[front] <= val){
					front++; break;
				}
				data[rear] = data[front];
				rear--;  director = 1;
				break;
			case 1:
				if (data[rear] >= val){
					rear--;break;
				}
				data[front] = data[rear];
				front++; director = 0;
				break;
			default:break;
		}
	}
	data[front] = val;
	return front;
}

//************************** 归并排序 *****************************************//
bool mergeSort(int* data, int begin,int end){
	if (end <= begin) return true;

	int med = (begin + end) / 2;
	mergeSort(data, begin, med);
	mergeSort(data, med+1, end);
	unic(data, begin, med, end);
	//cout << "------------------------------------" << endl;
	//cout << "begin : " << begin << "\tend" << end<<endl;
	//printArr(data, 11, 11);
	return true;
}
void unic(int* data, int begin, int med, int end){
	while (med++ <= end){
		insertSortX(data, med);
	}
}


//void heapSort(int* data, int length);   // 堆排序

//************************** 基数排序 *****************************************//
void radixSort(int* data, int length){
	int val;
	int digit = 1;
	int* offsetArr =(int*)createArrByType(INT_TYPE, 10);
	int* tmp = (int*)createArrByType(INT_TYPE, length);
	initArr(offsetArr, 10, 0);
	printArr(data, length, length);

	while (count(data, length, digit, offsetArr) == true){
		for (int i = 0; i < length; i++){
			val = data[i] / pow(10, digit - 1);
			val = val % 10;
			tmp[offsetArr[val]] = data[i];
			offsetArr[val]++;
		}
		cout << "---------------------data-------------------" << endl;
		printArr(tmp, length, length);
		cout << "---------------------data-------------------" << endl;
		initArr(offsetArr, 10, 0);
		digit++;
	}
	data = tmp;
}

bool count(int* data,int lenght, int digit,int* offsetArr){
	int val;
	bool mark = false;
	for (int i = 0; i < lenght; i++){
		val = data[i] / pow(10, digit - 1);
		if (val != 0) mark = true;
		val = val % 10;
		offsetArr[val]++;
	}
	cout << "************************************************************" << endl;
	printArr(offsetArr, 10, 10);
	cout << "---------------------------------" << endl;
	int beforeVal = offsetArr[0];
	int afterVal = 0;
	for (int i = 1; i < 10; i++){
		afterVal  = beforeVal + afterVal;
		beforeVal = offsetArr[i];
		offsetArr[i] = afterVal;
	}
	offsetArr[0] = 0;
	printArr(offsetArr, 10, 10);
	cout << "************************************************************" << endl<<endl;
	return mark;
}
