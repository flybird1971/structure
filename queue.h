/*
 * This file implements queue by single linked list
 * ʹ�õ����� ʵ�ֶ���
 *
 * author flybird1971@gmail.com
 * since  2015-05-12
 */
#pragma once
#include <stdio.h>
#include "error_code.h"

typedef int queueValType;

//������ڵ�
typedef struct queue_node{
	queue_node * next;
	queueValType value;
}qNode, *pQNode;

//���еĶ���
typedef struct Queue_type{
	pQNode front, rear;
	unsigned int length;
}queue, *pQueue;

typedef void(*dealQ)(queueValType &);

/* 6 basic operation  */

bool initQueue(queue & qList);

bool clearQueue(queue &qList);

bool destoryQueue(queue &qList);

bool pushQueue(queue &qList, queueValType val);

bool popQueue(queue &qList, queueValType &val);

int  getQueueLength(queue qList);

void travservalQueue(queue &qList, dealQ fun);

void fun(queueValType &);