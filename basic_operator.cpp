#pragma once

#include"stdafx.h"
#include "error_code.h"
#include <iostream>
#include <stdlib.h>
#include "sql.h"

using namespace std;

//��ʼ������
void initList(SQLIST &list){

	list.pArr = (int(*)[])malloc(sizeof(int) * STATIC_QUEUE_SIZE);
	list.size = STATIC_QUEUE_SIZE;
	list.length = 0;
	cout << "initial successful"<<endl;
}

//���ٶ���
void desctoryList(SQLIST &list){

	free(list.pArr);
	list.pArr = NULL;
	list.size = 0;
	list.length = 0;
	cout << "destoryList successful" << endl;
}

//��ն���
void clearList(SQLIST &list){
	list.length = 0;
	cout << "clearList successful" << endl;
}

//�ж϶����Ƿ�Ϊ��
bool emptyList(SQLIST list){
	return list.length == 0;
}

//��ȡ����Ԫ��
int getElement(SQLIST list, int postion, int &ele){

	if (postion >= list.length || postion < 0) return STATIC_QUEUE_OVERFLOW;

	if (list.length == 0) return STATIC_QUEUE_IS_EMPTY;

	ele = (*list.pArr)[postion];
	return OK;
}

//��ȡ���г���
int getLength(SQLIST list){
	return list.length;
}

//����Ԫ������λ��
int locateElement(SQLIST list, int ele){

	for(int index = 0; index < list.length; index++){
		if ((*list.pArr)[index] == ele) return index;
	}
	return STATIC_QUEUE_ELEMENT_NO_EXIST;
}

//��ȡǰ��
int getProvion(SQLIST list, int ele, int &provionEle){

	int index = locateElement(list, ele);
	if (STATIC_QUEUE_ELEMENT_NO_EXIST == index ) return STATIC_QUEUE_ELEMENT_NO_EXIST;
	if (index == 0) return STATIC_QUEUE_ELEMENT_IS_FIRST;
	provionEle = (*list.pArr)[index - 1];
	return OK;
}

//��ȡ���
int getNext(SQLIST list, int ele, int &nextEle){

	int index = locateElement(list, ele);
	if (STATIC_QUEUE_ELEMENT_NO_EXIST == index) return STATIC_QUEUE_ELEMENT_NO_EXIST;
	if (index == (list.length - 1)) return STATIC_QUEUE_ELEMENT_IS_LAST;
	nextEle = (*list.pArr)[index + 1];
	return OK;
}

//����Ԫ��
int insertElement(SQLIST &list, int pos, int newEle){
	if (pos < 0 || pos > list.length) return STATIC_QUEUE_OVERFLOW;

	//�����ڴ�
	if (list.length == list.size){
		void* pTmp = realloc(list.pArr, sizeof(int)*list.size * 2);
		if (pTmp == NULL){
			list.pArr = NULL;
			list.length++;
			return ALLOCA_ERROR;
		}
		list.pArr = (int(*)[])pTmp;
		pTmp = NULL;
		list.size *= 2;
		(*list.pArr)[list.length] = newEle;
		list.length++;
		return OK;
	}

	for (int index = list.length - 1; index >= pos; index--){
		(*list.pArr)[index + 1] = (*list.pArr)[index];
	}
	(*list.pArr)[pos] = newEle;
	list.length++;
	//cout << "insertElement successful"<<list.length << endl;
	return OK;
}

//ɾ��Ԫ��
int deleteElement(SQLIST &list, int postion, int &oldEle){

	if (postion < 0 || postion > list.length - 1) return STATIC_QUEUE_OVERFLOW;
	
	oldEle = (*list.pArr)[postion];
	for (int index = postion; index < list.length-1; index++){
		(*list.pArr)[index] = (*list.pArr)[index + 1];
	}
	list.length--;
	cout << "delete element successful" << endl;
	return OK;
}

//��������
void traversalList(SQLIST &list){

	for (int index = 0; index < list.length; index++){

		cout << " ���е�" << index + 1 << "��ֵ �� " << (*list.pArr)[index] << endl;
	}
}