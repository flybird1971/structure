/*
* This file implements queue by array
* ʹ������ ʵ�ֶ���
*
* author flybird1971@gmail.com
* since  2015-05-15
*/
#pragma once
#include <stdio.h>
#include "error_code.h"

const int ARRAY_QUEUE_LENGTH = 100;
typedef int arrayQueueType;

//�ڵ�
typedef struct array_queue{
	arrayQueueType values[ARRAY_QUEUE_LENGTH];
	unsigned int front, rear;
}arrayQueue,*pArrayQueue;

typedef void(*dealAQ)(arrayQueueType &);

/* 6 basic operation  */
bool initArrayQueue(arrayQueue & qList);

bool clearArrayQueue(arrayQueue &qList);

bool destoryArrayQueue(arrayQueue &qList);

bool getFrontArrayQueue(arrayQueue qList, arrayQueueType &val);

bool pushArrayQueue(arrayQueue &qList, arrayQueueType val);

bool popArrayQueue(arrayQueue &qList, arrayQueueType &val);

int  getArrayQueueLength(arrayQueue qList);

void travservalArrayQueue(arrayQueue &qList, dealAQ funAQ);

void travservalArrayQ(arrayQueue &qList);

void funAQ(arrayQueueType &);