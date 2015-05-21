/*
* ��
*
* author flybird1971@gmail.com
* since  2015-05-19
*/
#pragma once

#include"stdafx.h"
#include "error_code.h"
#include <iostream>
#include "bTree.h"

using namespace std;

//********************* �������� ***********************
//��������ʽ����������
pBTree createBTree(bTreeType dataArr[], int length,int index){
	if (index > length || dataArr[index-1] == '#') return NULL;
	pBTree pBT = createBTree(dataArr[index-1]);
	if(pBT!=NULL) pBT->leftChird  = createBTree(dataArr, length, index * 2);
	if(pBT!=NULL) pBT->rightChird = createBTree(dataArr, length, index * 2+1);
	return pBT;
}

//����ֻ�����Ķ�����
pBTree createBTree(bTreeType val){
	void * tmpP = malloc(sizeof(bTreeNode));
	if (tmpP == NULL) return NULL;
	pBTree pRes = (pBTree)tmpP;
	pRes->leftChird = pRes->rightChird = NULL;
	pRes->val = val;
	return pRes;
}

//ʹ���Ѿ����ڵĶ����������д���
pBTree createBTree(pBTree oldTree){
	if (oldTree == NULL) return NULL;
	pBTree pRes = createBTree(oldTree->val);
	pRes->leftChird  = createBTree(oldTree->leftChird);
	pRes->rightChird = createBTree(oldTree->rightChird);
	return pRes;
}

//���ٶ�����
bool destoryBTree(pBTree &pTr){
	if (pTr == NULL) return false;
	destoryBTree(pTr->leftChird);
	destoryBTree(pTr->rightChird);
	free(pTr);
	pTr = NULL;
	return true;
}

//����
pBTree locateBTree(pBTree pTr, bTreeType val){
	if (pTr == NULL) return NULL;
	if(pTr->val == val)  return pTr;
	pBTree pRes = locateBTree(pTr->leftChird,val);
	if (pRes != NULL) return pRes;
	pRes = locateBTree(pTr->rightChird, val);
	if (pRes != NULL) return pRes;
	return NULL;
}

//��������
pBTree insertBTree(pBTree pTr, bTreeType val, int dirctor){
	if (pTr == NULL) return NULL;
	pBTree pRes = createBTree(val);
	switch (dirctor){
		case BIN_TREE_DIRECTOR_SELF :
			pTr->val = val;
			free(pRes);
			return pTr;
		case BIN_TREE_DIRECTOR_LEFT:
			if (pTr->leftChird != NULL) return NULL;
			pTr->leftChird = pRes;
			return pRes;
		case BIN_TREE_DIRECTOR_RIGHT:
			if (pTr->rightChird != NULL) return NULL;
			pTr->rightChird = pRes;
			return pRes;
		default: return NULL;
	}
}

//��������
pBTree insertBTree(pBTree pTr, pBTree decedent, int dirctor){
	if (pTr == NULL || decedent == NULL) return NULL;
	switch (dirctor){
		case BIN_TREE_DIRECTOR_LEFT : 
			if (pTr->leftChird != NULL) return NULL;
			pTr->leftChird = createBTree(decedent);
			return pTr->leftChird;
		case BIN_TREE_DIRECTOR_RIGHT:
			if (pTr->rightChird != NULL) return NULL;
			pTr->leftChird = createBTree(decedent);
			return pTr->leftChird;
		default: return NULL;
	}
}

//ɾ���ڵ�
bool deleteBTree(pBTree pTr, bTreeType val){
	pTr = getBTreeParent(pTr, val);
	if (pTr == NULL) return false;
	if (pTr->leftChird != NULL && pTr->leftChird->val == val) destoryBTree(pTr->leftChird);
	if (pTr->rightChird != NULL && pTr->rightChird->val == val) destoryBTree(pTr->rightChird);
	return true;
}

//��ȡ���ڵ�
pBTree getBTreeParent(pBTree pTr, bTreeType val){
	if (pTr == NULL) return NULL;
	if (pTr->leftChird != NULL && pTr->leftChird->val == val) return pTr;
	if (pTr->rightChird != NULL && pTr->rightChird->val == val) return pTr;
	pBTree pRes = getBTreeParent(pTr->leftChird,val);
	if (pRes != NULL) return pRes;
	pRes = getBTreeParent(pTr->rightChird, val);
	if (pRes != NULL) return pRes;
	return NULL;
}

//��ȡ�ֵܽڵ�
pBTree getBTreeSibling(pBTree pTr, bTreeType val){
	pBTree pParentTree = getBTreeParent(pTr, val);
	if (pParentTree == NULL) return NULL;
	if (pParentTree->leftChird != NULL && pParentTree->leftChird->val == val) return pParentTree->rightChird;
	if (pParentTree->rightChird != NULL && pParentTree->rightChird->val == val) return pParentTree->leftChird;
	return NULL;
}

//��ȡ����
pBTree getBTreeLeftChird(pBTree pTr, bTreeType val){
	pBTree pCurrent = locateBTree(pTr, val);
	if (pCurrent == NULL) return NULL;
	return pCurrent->leftChird;
}

//��ȡ�Һ���
pBTree getBTreeRightChird(pBTree pTr, bTreeType val){
	pBTree pCurrent = locateBTree(pTr, val);
	if (pCurrent == NULL) return NULL;
	return pCurrent->rightChird;
}

//��ȡ����
int  getBTreeDepth(pBTree pTr){
	if (pTr == NULL) return 0;
	int depth = 0;
	int maxDepth = 0;
	depth = 1 + getBTreeDepth(pTr->leftChird);
	maxDepth = maxDepth > depth ? maxDepth : depth;
	depth = 1 + getBTreeDepth(pTr->rightChird);
	maxDepth = maxDepth > depth ? maxDepth : depth;
	return maxDepth;
}

//�ж��Ƿ�Ϊ��
bool isEmptyBTree(pBTree pTr){
	if (pTr == NULL) return true;
	return pTr->leftChird==NULL || pTr->rightChird == NULL;
}

//ǰ����� ������� �������
bool traversalBTree(pBTree pTr, dealBTree dealBTS,int order){
	if (pTr == NULL) return false;
	if (order == BIN_TREE_TRAVERSAL_PREORDER) dealBTS(pTr->val);
	traversalBTree(pTr->leftChird, dealBTS, order);
	if (order == BIN_TREE_TRAVERSAL_INORDER) dealBTS(pTr->val);
	traversalBTree(pTr->rightChird, dealBTS, order);
	if (order == BIN_TREE_TRAVERSAL_POSTORDER) dealBTS(pTr->val);
	return true;
}

//ǰ����� ������� �������
bool traversalBTree(pBTree pTr, dealBTEx dealBTreeEx, int order, stack &Stack){
	char val = '\0';
	if (pTr == NULL) return false;
	if (order == BIN_TREE_TRAVERSAL_PREORDER) dealBTreeEx(pTr,Stack);
	if(traversalBTree(pTr->leftChird, dealBTreeEx, order,Stack)==true) popStack(Stack, val);
	if (order == BIN_TREE_TRAVERSAL_INORDER) dealBTreeEx(pTr, Stack);
	if(traversalBTree(pTr->rightChird, dealBTreeEx, order, Stack)) popStack(Stack, val);
	if (order == BIN_TREE_TRAVERSAL_POSTORDER) dealBTreeEx(pTr, Stack);
	return true;
}

//����������
void dealBT(bTreeType &val){
	cout << val << "\t";
}

//����������
void dealBTreeEx(pBTree pTr, stack &Stack){
	char val = '\0';
	pushStack(Stack, pTr->val);
	int depth = getBTreeDepth(pTr);
	if (depth == 1){
		cout << " leaf path is : " << endl;
		travservalStack(Stack);
	}
}