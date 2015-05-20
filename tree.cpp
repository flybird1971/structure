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
#include "tree.h"

using namespace std;

//********************* �������� ***********************
//��������
pTree createTree(treeType val=0){
	void *tmpP = malloc(sizeof(treeNode));
	if (tmpP == NULL) return NULL;
	pTree pTr = (pTree)tmpP;
	pTr->decendent = pTr->sibling = NULL;
	pTr->val = val;
	return pTr;
}

//ʹ���Ѿ����ڵ��� ����
pTree createTree( pTree oldTree){  
	pTree pTr = createTree(0);
	copyTree(pTr, oldTree,TREE_DIRECTOR_SELF);
	return pTr;
}

//����
bool copyTree(pTree pTr, pTree oldTree, int director = TREE_DIRECTOR_SELF){
	if (oldTree == NULL || pTr == NULL) return false;
	if (director == 0 && pTr->decendent != NULL) destoryTree(pTr->decendent);
	if (director == 1 && pTr->sibling != NULL) destoryTree(pTr->sibling);
	pTree pTrTmp = insertTree(pTr, oldTree->val, director);
	copyTree(pTrTmp, oldTree->sibling, TREE_DIRECTOR_SILING);
	copyTree(pTrTmp, oldTree->decendent, TREE_DIRECTOR_DECENDENT);
	return true;
}

//����
bool destoryTree(pTree &pTr){ 
	if (pTr==NULL) return false;
	destoryTree(pTr->decendent);
	destoryTree(pTr->sibling);
	free(pTr);
	pTr = NULL;
	return true;
}

//����Ԫ�أ���������
pTree locateTree(pTree pTr, treeType val,bool getPrevious){
	if (pTr == NULL) return NULL;
	if (getPrevious == true){
		if ((pTr->decendent != NULL && pTr->decendent->val == val) ||
			(pTr->sibling != NULL&& pTr->sibling->val == val)) {
			return pTr;
		}
	}else{
		if (pTr->val == val) return pTr;
	}
	pTree pRes;
	pRes = locateTree(pTr->decendent, val,getPrevious);
	if (pRes != NULL) return pRes;
	pRes = locateTree(pTr->sibling, val,getPrevious);
	if (pRes != NULL) return pRes;
	return NULL;
}

//�ڵ�׷��,Ҳ�����ڸ�ֵ
pTree insertTree(pTree pTr, treeType val,int dirctor){     
	if (pTr == NULL) return NULL;
	void *tmpP = malloc(sizeof(treeNode));
	if (tmpP == NULL) return NULL;
	switch (dirctor){
		case TREE_DIRECTOR_SELF:
			pTr->val = val;
			free(tmpP);
			return pTr;
		case TREE_DIRECTOR_DECENDENT:
			if (pTr->decendent != NULL) return NULL;
			pTr->decendent = (pTree)tmpP;
			pTr->decendent-> val = val;
			pTr->decendent->decendent = pTr->decendent->sibling = NULL;
			return pTr->decendent;
		case TREE_DIRECTOR_SILING:
			if (pTr->sibling != NULL) return NULL;
			pTr->sibling = (pTree)tmpP;
			pTr->sibling->val = val;
			pTr->sibling->decendent = pTr->sibling->sibling = NULL;
			return pTr->sibling;
		default: return NULL;
	}
}

//����׷�ӽڵ�
pTree insertTree(pTree pTr, pTree decedent,int dirctor){
	if (pTr == NULL || decedent==NULL) return NULL;
	switch (dirctor){
		case TREE_DIRECTOR_DECENDENT:
			if (pTr->decendent != NULL) return NULL;
			if (copyTree(pTr, decedent, TREE_DIRECTOR_DECENDENT) == false) return NULL;
			return pTr->decendent;
		case TREE_DIRECTOR_SILING:
			if (pTr->sibling != NULL) return NULL;
			if (copyTree(pTr, decedent, TREE_DIRECTOR_SILING) == false) return NULL;
			return pTr->sibling;
		default: return NULL;
	}
}

//�ڵ�ɾ��
bool deleteTree(pTree pTr, treeType val){     
	pTr = locateTree(pTr,val,true);
	pTree pTmp = NULL;
	if (pTr == NULL) return false;
	if (pTr->sibling!=NULL && pTr->sibling->val == val){
		pTmp = pTr->sibling->sibling;
		destoryTree(pTr->sibling->decendent);
		free(pTr->sibling);
		pTr->sibling = pTmp;
	}
	if (pTr->decendent!=NULL && pTr->decendent->val == val){
		pTmp = pTr->decendent->sibling;
		destoryTree(pTr->decendent->decendent);
		free(pTr->decendent);
		pTr->decendent = pTmp;
	}
	return true;
}

//��ȡ���ڵ�
bool getParent(pTree pTr, treeType val,pTree &parentNode){    
	if (pTr == NULL) return false;
	if (pTr->val == val) return true;
	pTree nextNode = pTr->decendent;
	while (nextNode!=NULL){
		if (getParent(nextNode, val, parentNode) == false){
			nextNode = nextNode->sibling;
		}else{
			parentNode =  parentNode != NULL ? parentNode : pTr;
			return true;
		}
	}
	return false;
}

//��ȡ�ֵܽڵ�
pTree getSibling(pTree pTr, treeType val){
	pTree parentPTree = NULL;
	getParent(pTr, val, parentPTree);
	if (parentPTree == NULL) return NULL;
	return parentPTree->decendent;
}

//��ȡ����
pTree getDecendent(pTree pTr, treeType val){  
	pTree pTrTmp = locateTree(pTr, val,false);
	if (pTrTmp == NULL) return NULL;
	return pTrTmp->decendent;
}

//��ȡ����
int  getTreeDepth(pTree pTr){    
	if (pTr == NULL) return 0;
	int depth = 0;
	int maxDepth = 0;
	depth = 1 + getTreeDepth(pTr->decendent);
	maxDepth = maxDepth > depth ? maxDepth : depth;
	depth =  getTreeDepth(pTr->sibling);
	maxDepth = maxDepth > depth ? maxDepth : depth;
	return maxDepth;
}

//�ж����Ƿ�Ϊ��
bool isEmptyTree(pTree pTr){ 
	if (pTr == NULL) return true;
	return pTr->decendent == NULL;
}

//������
bool traversalTree(pTree pTr, dealTree dealF){  
	if (pTr == NULL) return false;
	dealF(pTr->val);
	traversalTree(pTr->decendent, dealF);
	traversalTree(pTr->sibling, dealF);
	return true;
}

void dealF(treeType &val){
	//val = val + 10;
	cout << val << "\t";
}


//����
/*
bool createTree(pTree pTr, treeType val){
	if (pTr == NULL) return false;
	if (pTr->decendent != NULL || pTr->sibling != NULL){
		destoryTree(pTr->decendent);
		destoryTree(pTr->sibling);
	}
	pTr->decendent = pTr->sibling = NULL;
	pTr->val = val;
	return true;
}

pTree createTree(pTree pTr,int index, treeType dataArr[], int offsetArr[], int length){
	if (pTr->decendent != NULL || pTr->sibling != NULL) destoryTree(pTr);
	if (index >= length || pTr==NULL) return NULL;
	int timer = 0;
	pTree pTr = insertTree(pTr, dataArr[index], 0);
	while (timer < offsetArr[index]){
	pTr = createTree(pTr, index + timer, dataArr, offsetArr, length);
	timer++;
	}
}
//*/