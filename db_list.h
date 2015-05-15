/*
 * This file implements doubly linked list
 * 实现双向循环链表
 *
 * author flybird1971@gmail.com
 * since  2015-05-12
 */
#pragma once
#include <stdio.h>
#include "error_code.h"

typedef  int statuCode;
typedef  int eleType;

//define node
typedef struct doubly_list_node {
	doubly_list_node * prev;
	doubly_list_node * next;
	eleType  value;
}dbNode,  *pDbNode;

//define doubly list
typedef struct doubly_list{
	pDbNode  head, tail;
	int length;
}dbList,*pDbList;

typedef  void(*dealFun)(eleType &);


/* 12 basic operations */

//initialize doubly linked list
bool initDbList(dbList &pDbList);

//clear doubly linked list
bool clearDbList(dbList &pDbList);

//clear doubly linked list
bool destoryDbList(dbList &pDbList);

//jugde doubly linked list is empty
bool isEmptyDbList(dbList pDbList);

//get doubly linked list length
int  getDbListLength(dbList pDbList);

//insert new element into doubly linked list 
statuCode insertElementDbList(dbList &pDbList, int index, eleType newEle);

//get element by index
statuCode getElementDbList(dbList pDbList, int index, eleType &ele);

//find element is exists or index
int  locateDbList(dbList pDbList, eleType ele);

//delete ele of index  and put old val into oldEle
statuCode delElementDbList(dbList &pDbList, int index, eleType &oldEle);

//get previous driver
statuCode getPreviousDbList(dbList pDbList, eleType value, pDbNode &previon);

//get next driver
statuCode getNextDbList(dbList pDbList, eleType value, pDbNode &next);

//traversal doubly linked list and todo ...
void traversalDbList(dbList &pDbList, dealFun fun);

void traversal(dbList pDbList);

void dealT(eleType &ele);


