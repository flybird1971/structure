#pragma once

#include <stdio.h>
#include <iostream>
using namespace std;


//���徲̬�б�Ĵ�С
const int   STATIC_QUEUE_SIZE = 100 ;


// TODO: reference additional headers your program requires here
//���徲̬���������б�
 typedef struct static_list{

	 //��̬���飬���ڴ洢����
	 int (*pArr)[];

	 //��̬���д�С
	 int size;

	 //��̬���д洢Ԫ�ظ���
	 int length;
}SQLIST;

 /***************** ������̬���е�12�ֳ��÷��� ***************************/
 //��ʼ����̬����
 void initList(SQLIST &list);

 //���پ�̬����
 void destoryList(SQLIST &list);

 //��վ�̬����
 void clearList(SQLIST &list);

 //�жϾ�̬�����Ƿ�Ϊ��
 bool emptyList(SQLIST list);
 
 //����Ԫ��
 int insertElement(SQLIST &list,int pos, int newEle);
 
 //ɾ��Ԫ��
 int deleteElement(SQLIST &list, int postion, int &oldEle);
 
 //��ȡָ��λ��Ԫ��
 int getElement(SQLIST list,int postion, int &ele);
 
 //����Ԫ��
 int locateEle(SQLIST list, int ele);
 
 //���г���
 int getLenght(SQLIST list);

 //��ȡǰ��
 int getProvion(SQLIST list, int element, int &provion);
 
 //��ȡ���
 int getNext(SQLIST list, int element, int &next);

 //��������
 void traversalList(SQLIST &list);