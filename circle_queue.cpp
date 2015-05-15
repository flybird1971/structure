/*
* This file implements queue by single linked list
* 使用单链表 实现队列
*
* author flybird1971@gmail.com
* since  2015-05-12
*/

#pragma once

#include"stdafx.h"
#include "error_code.h"
#include <iostream>
#include "circle_queue.h"

using namespace std;

/* 6 basic operation  */
bool initArrayQueue(arrayQueue & qList){
	qList.front = qList.rear = 0;
	return true;
}

bool clearArrayQueue(arrayQueue &qList){
	qList.front = qList.rear = 0;
	return true;
}

bool destoryArrayQueue(arrayQueue &qList){
	qList.front = qList.rear = 0;
	return true;
}

bool getFrontArrayQueue(arrayQueue qList, arrayQueueType &val){
	if (qList.front == qList.rear) return false;
	val = qList.values[qList.front];
	return true;
}

bool pushArrayQueue(arrayQueue &qList, arrayQueueType val){
	if ((qList.rear + 1) % ARRAY_QUEUE_LENGTH == qList.front) return false;
	qList.values[qList.rear] = val;
	qList.rear = (qList.rear + 1) % ARRAY_QUEUE_LENGTH;
	return true;
}

bool popArrayQueue(arrayQueue &qList, arrayQueueType &val){
	if (qList.rear == qList.front) return false;
	val = qList.values[qList.front];
	qList.front = (qList.front + 1) % ARRAY_QUEUE_LENGTH;
	return true;
}

int  getArrayQueueLength(arrayQueue qList){
	return (qList.rear - qList.front + ARRAY_QUEUE_LENGTH) % ARRAY_QUEUE_LENGTH;
}

void travservalArrayQueue(arrayQueue &qList, dealAQ funAQ){
	unsigned int tmpIndex = qList.front;
	while (tmpIndex != qList.rear){
		funAQ(qList.values[tmpIndex]);
		tmpIndex = (tmpIndex+1)%ARRAY_QUEUE_LENGTH;
	}
}

void travservalArrayQ(arrayQueue &qList){
	unsigned int tmpIndex = qList.front;
	while (tmpIndex != qList.rear){
		//cout<<"index is "<<tmpIndex<<"\t value is " << qList.values[tmpIndex] << endl;
		if(qList.values[tmpIndex] > 0 ) cout << qList.values[tmpIndex] << "\t";
		tmpIndex = (tmpIndex + 1) % ARRAY_QUEUE_LENGTH;
	}
	cout << endl;
}

void funAQ(arrayQueueType &ele){
	ele = ele + 1;
}