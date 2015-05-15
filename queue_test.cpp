/*
* This file implements doubly linked list
* 队列 测试
*
* author flybird1971@gmail.com
* since  2015-05-15
*/
#pragma once

#include"stdafx.h"
#include "error_code.h"
#include <iostream>
#include "queue_test.h"

using namespace std;

//杨辉三角,使用循环队列处理
bool triangleDeal(){
	cout << "enter int value (gt 2) : " << endl;
	int level;
	cin >> level;
	while (level > 0){
		if (level < 2) return false;
		arrayQueue circleQueue;
		initArrayQueue(circleQueue);
		pushArrayQueue(circleQueue, 0);
		pushArrayQueue(circleQueue, 1);
		pushArrayQueue(circleQueue, 0);
		travservalArrayQ(circleQueue);
		for (int i = 2; i <= level; i++){
			int tmpVal, frontVal, times;
			tmpVal = frontVal = 0;
			times = i + 1;
			while (times-- > 0){
				if (popArrayQueue(circleQueue, frontVal) == false) return false;
				tmpVal += frontVal;
				pushArrayQueue(circleQueue, tmpVal);
				tmpVal = frontVal;
			}
			pushArrayQueue(circleQueue, 0);
			travservalArrayQ(circleQueue);
		}
		cout << " -------------------------------------- " << endl;
		cin >> level;
	}
}

//调试 循环队列
void debugCircleQueue(){
	arrayQueue aQueue;
	initArrayQueue(aQueue);
	cout << "circle lenght is " << getArrayQueueLength(aQueue) << endl;
	arrayQueueType tmpVal;
	if (getFrontArrayQueue(aQueue, tmpVal) == false){
		cout << "circle queue is empty";
	}
	else{
		cout << "circle queue front is " << tmpVal << endl;
	}

	for (int i = 0; i < 1000; i++){
		if (pushArrayQueue(aQueue, i) == false){
			cout << "queue is full ";
			break;
		}
		else{
			//cout << "push value " << i << " into queue" << endl;
		}
	}

	//travservalArrayQ(aQueue);
	travservalArrayQueue(aQueue, funAQ);
	//travservalArrayQ(aQueue);
	//cout << "queue length is " << getArrayQueueLength(aQueue) << endl;
	//getFrontArrayQueue(aQueue, tmpVal);
	//cout << "queue front value is " << tmpVal<< endl;
	//cout << "queue length is " << getArrayQueueLength(aQueue) << endl;
	clearArrayQueue(aQueue);
	destoryArrayQueue(aQueue);
	arrayQueueType tmpVal2;
	popArrayQueue(aQueue, tmpVal2);
	cout << "queue pop value is " << tmpVal2 << endl;
	cout << "queue length is " << getArrayQueueLength(aQueue) << endl;

}

//调试 单链表实现的队列
void debugQueue(){

	queue qNew;
	initQueue(qNew);
	cout << " --------------- init after --------------" << endl;
	cout << "is length " << qNew.length << endl;
	travservalQueue(qNew, fun);
	int max = 10;
	int index = 0;
	for (int i = 0; i < max; i++){
		if (pushQueue(qNew, i) == false){
			cout << "push error index is : " << index++ << "\t value is " << i << endl;
		}
		else{
			cout << "push success index is " << index++ << "\t value is " << i << endl;
		}
	}
	cout << " --------------- push after --------------" << endl;
	clearQueue(qNew);
	//travservalQueue(qNew, fun);
	cout << "is length " << qNew.length << endl;
	int ele = 0;
	max = qNew.length / 2;
	for (int i = 0; i < max; i++){
		if (popQueue(qNew, ele) == false){
			cout << "pop error index is : " << i << endl;
		}
		else{
			cout << "pop success index is : " << i << "\t value is " << ele << endl;
		}
	}
	cout << " --------------- pop after --------------" << endl;
	travservalQueue(qNew, fun);
	cout << "is length " << qNew.length << endl;
	destoryQueue(qNew);
}