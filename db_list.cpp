/*
 * doubly linked list 12 basic implemeentions
 *
 * author flybird1971@gmail.com
 * since  2015-05-12
 */

#pragma once

#include"stdafx.h"
#include "error_code.h"
#include <iostream>
#include <stdlib.h>
#include "db_list.h"


using namespace std;

//initialize circle doubly linked list
bool initDbList(dbList &pDbList){
	void * tmpP = malloc(sizeof(dbNode));
	if (tmpP == NULL) return false;
	pDbList.head = (pDbNode)tmpP;

	tmpP = malloc(sizeof(dbNode));
	if (tmpP == NULL) return false;
	pDbList.tail = (pDbNode)tmpP;
	tmpP = NULL;

	pDbList.head->next = pDbList.head->next = pDbList.tail;
	pDbList.tail->prev = pDbList.tail->next = pDbList.head;
	pDbList.length =  0;
	return true;
}

//clear doubly linked list
bool clearDbList(dbList &pDbList){
	pDbNode pCurren, pNext;
	pCurren = pDbList.head->next;
	while (pCurren != pDbList.tail){
		pNext = pCurren->next;
		free(pCurren);
		pCurren = pNext;
	}
	pCurren = pNext = NULL;
	pDbList.head->prev = pDbList.head->next = pDbList.tail;
	pDbList.tail->prev = pDbList.tail->next = pDbList.head;
	pDbList.length = 0;
	return true;
}

//clear doubly linked list
bool destoryDbList(dbList &pDbList){
	pDbNode pCurrent, pNext;
	pCurrent = pDbList.head->next;
	while (pCurrent != pDbList.tail){
		pNext = pCurrent->next;
		free(pCurrent);
		pCurrent = pNext;
	}
	free(pDbList.head);
	free(pDbList.tail);
	pCurrent = pNext = pDbList.head = pDbList.tail = NULL;
	pDbList.length = NULL;
	return true;
}

//jugde doubly linked list is empty
bool isEmptyDbList(dbList pDbList){
	return pDbList.length == 0 && pDbList.head != NULL;
}

//get doubly linked list length
int  getDbListLength(dbList pDbList){
	return pDbList.head == NULL ? -1 : pDbList.length;
}

//insert new element into doubly linked list 
statuCode insertElementDbList(dbList &pDbList, int index, eleType newEle){
	if (index<0 || index>pDbList.length) return DOUBLY_LIST_OVERFLOW;
	pDbNode pCurrent,pNewNode;
	
	//malloc 
	void * tmpP = malloc(sizeof(dbNode));
	if (tmpP == NULL) return false;
	pNewNode = (pDbNode)tmpP;
	tmpP = NULL;

	//insert
	pCurrent = pDbList.head->next;
	while (index-- > 0){
		pCurrent = pCurrent->next;
	}
	pNewNode->next  = pCurrent;
	pNewNode->prev  = pCurrent->prev;
	//cout <<"before insert : "<< pNewNode->value << " new elemement "<< newEle<< endl;
	pNewNode->value = newEle;
	//cout << "after insert : " << pNewNode->value << " new elemement " << newEle << endl;
	pCurrent->prev->next = pNewNode;
	pCurrent->prev  = pNewNode;
	pDbList.length++;
	return OK;
}

//get element by index
statuCode getElementDbList(dbList pDbList, int index, eleType &ele){
	if (index < 0 || index >= pDbList.length) return DOUBLY_LIST_OVERFLOW;
	pDbNode pCurrent, pNext;
	pCurrent = pDbList.head->next;
	while (index-- > 0){
		pCurrent = pCurrent->next;
	}
	ele = pCurrent->value;
	return OK;
}

//find element is exists or index
int  locateDbList(dbList pDbList, eleType ele){
	int index = 0;
	pDbNode pCurrent, pNext;
	pCurrent = pDbList.head->next;
	while (pCurrent != pDbList.tail){
		if (ele != pCurrent->value){
			pCurrent = pCurrent->next;
			index++;
			continue;
		}
		return index;
	}
	return DOUBLY_LIST_NOT_EXISTS;
}

//delete ele of index  and put old val into oldEle
statuCode delElementDbList(dbList &pDbList, int index, eleType &oldEle){
	if (index < 0 || index >= pDbList.length) return DOUBLY_LIST_OVERFLOW;
	if (pDbList.length <= 0) return OK;
	pDbNode pCurrent, pNext;
	pCurrent = pDbList.head->next;
	while (index-- > 0){
		pCurrent = pCurrent->next;
	}
	pCurrent->prev->next = pCurrent->next;
	pCurrent->next->prev = pCurrent->prev;
	oldEle = pCurrent->value;
	free(pCurrent);
	pDbList.length--;
	pCurrent = NULL;
	return OK;
}

//get previous driver
statuCode getPreviousDbList(dbList pDbList, eleType value, pDbNode &previon){
	pDbNode pCurrent = pDbList.head->next;
	while (pCurrent != pDbList.tail){
		if (pCurrent->value != value){
			pCurrent = pCurrent->next;
			continue;
		}

		if (pCurrent->prev == pDbList.head) return DOUBLY_LIST_NOT_PREVIOUS;
		previon = pCurrent->prev;
		return OK;
	}
	return DOUBLY_LIST_NOT_EXISTS;
}

//get next driver
statuCode getNextDbList(dbList pDbList, eleType value, pDbNode &next){
	pDbNode pCurrent = pDbList.head->next;
	while (pCurrent != pDbList.tail){
		if (pCurrent->value != value){
			pCurrent = pCurrent->next;
			continue;
		}

		if (pCurrent->next == pDbList.tail) return DOUBLY_LIST_NOT_NEXT;
		next = pCurrent->next;
		return OK;
	}
	return DOUBLY_LIST_NOT_EXISTS;
}

//traversal doubly linked list and todo ...
void traversalDbList(dbList &pDbList, dealFun fun){
	pDbNode pCurrent = pDbList.head->next;
	while (pCurrent != pDbList.tail){
		fun(pCurrent->value);
		pCurrent = pCurrent->next;
	}
}

void traversal(dbList pDbList){
	int index = 0;
	pDbNode pCurrent = pDbList.head->next;
	while (pCurrent != pDbList.tail){
		cout << "index : " << index++ << "\t value : " << pCurrent->value << endl;
		pCurrent = pCurrent->next;
	}
	cout << "doubly linked list length is : "<<pDbList.length<<endl<<"............................................"<<endl;
}

//implement deal function
void dealT(eleType &ele){
	ele = ele*ele;
}