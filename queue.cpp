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
#include "queue.h"

using namespace std;

/* 6 basic operation  */
bool initQueue(queue & qList){
	void *tmpP = malloc(sizeof(qNode));
	if (tmpP == NULL)return false;
	qList.front = qList.rear = (pQNode)tmpP;

	qList.front->next = NULL;
	qList.length = 0;
	return true;
}

bool clearQueue(queue &qList){
	pQNode pCurrent, pNext;
	pCurrent = qList.front->next;
	while (pCurrent != NULL){
		pNext = pCurrent->next;
		free(pCurrent);
		pCurrent = pNext;
	}
	qList.rear = qList.front;
	qList.front->next = pCurrent = pNext  = NULL;
	qList.length = 0;
	return true;
}

bool destoryQueue(queue &qList){
	pQNode pCurrent, pNext;
	pCurrent = qList.front->next;
	while (pCurrent != NULL){
		pNext = pCurrent->next;
		free(pCurrent);
		pCurrent = pNext;
	}
	free(qList.front); 
	pCurrent = pNext = qList.front = qList.rear = NULL;
	qList.length = 0;
	return true;
}

bool pushQueue(queue &qList, queueValType val){
	void *tmpP = malloc(sizeof(qNode));
	if (tmpP == NULL) return false;
	pQNode pNewNode = (pQNode)tmpP;
	tmpP = NULL;
	
	qList.rear->next = pNewNode;
	qList.rear = pNewNode;
	pNewNode->next  = NULL;
	pNewNode->value = val;
	//cout << "length is " << qList.length << "\tvalue is " << val << endl;
	pNewNode = NULL;
	qList.length++;
	return true;
}

bool popQueue(queue &qList, queueValType &val){
	if (qList.length <= 0) return false;
	val = qList.front->next->value;
	//cout<<" pop queue " << qList.front->next->value << endl;
	pQNode pNextNode = qList.front->next->next;
	free(qList.front->next);
	qList.front->next = pNextNode;
	qList.length--;
	if (qList.length == 0) qList.rear = qList.front;
	return true;
}

int  getQueueLength(queue qList){
	return qList.length;
}

void travservalQueue(queue &qList, dealQ fun){
	pQNode pCurrent = qList.front->next;
	cout << "heloow" << endl;
	while (pCurrent != NULL){
		fun(pCurrent->value);
		pCurrent = pCurrent->next;
	}
}

bool locateQueue(queue qList, queueValType val){
	pQNode pCurrent = qList.front->next;
	while (pCurrent != NULL){
		if (pCurrent->value == val) return true;
		pCurrent = pCurrent->next;
	}
	return false;
}

void fun(queueValType &val){
	cout << val << "\t";
	val = val + 1;
}