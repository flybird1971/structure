/*
* ������
*
* author flybird1971@gmail.com
* since  2015-05-20
*/

#pragma once

#include <stdio.h>
#include <iostream>
#include "stack.h"

const int BIN_TREE_DIRECTOR_LEFT = 0;
const int BIN_TREE_DIRECTOR_RIGHT = 1;
const int BIN_TREE_DIRECTOR_SELF = -1;

const int BIN_TREE_TRAVERSAL_PREORDER  = 1;
const int BIN_TREE_TRAVERSAL_INORDER   = 2;
const int BIN_TREE_TRAVERSAL_POSTORDER = 3;
typedef char bTreeType;

//�������ڵ�
typedef struct bin_tree_node{
	bTreeType val;
	bin_tree_node* leftChird;
	bin_tree_node* rightChird;
}bTreeNode, *pBTreeNode, bTree, *pBTree;

typedef void(*dealBTree)(bTreeType &);
typedef void(*dealBTEx)(pBTree , stack &);


//********************* �������� ***********************
pBTree createBTree(bTreeType dataArr[], int length, int index);  //��������ʽ����������
pBTree createBTree(bTreeType val);    //����ֻ�����Ķ�����
pBTree createBTree(pBTree oldTree);   //ʹ���Ѿ����ڵĶ����������д���
bool destoryBTree(pBTree &pTr);       //���ٶ�����

pBTree locateBTree(pBTree pTr, bTreeType val);                //����
pBTree insertBTree(pBTree pTr, bTreeType val, int dirctor);   //��������
pBTree insertBTree(pBTree pTr, pBTree decedent, int dirctor); //��������
bool deleteBTree(pBTree pTr, bTreeType val);                  //ɾ���ڵ�

pBTree getBTreeParent(pBTree pTr, bTreeType val);     //��ȡ���ڵ�
pBTree getBTreeSibling(pBTree pTr, bTreeType val);    //��ȡ�ֵܽڵ�
pBTree getBTreeLeftChird(pBTree pTr, bTreeType val);  //��ȡ����
pBTree getBTreeRightChird(pBTree pTr, bTreeType val); //��ȡ�Һ���

int  getBTreeDepth(pBTree pTr);  //��ȡ����
bool isEmptyBTree(pBTree pTr);   //�ж��Ƿ�Ϊ��

void dealBT(bTreeType &val);            //����������
void dealBTreeEx(pBTree pTr, stack &Stack);//����������
bool traversalBTree(pBTree pTr, dealBTree dealBTS, int order); //ǰ����� ������� �������
bool traversalBTree(pBTree pTr, dealBTEx dealBTreeEx, int order, stack &Stack);