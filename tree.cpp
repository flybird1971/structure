/*
* 树
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

//********************* 基本操作 ***********************
//创建树根
pTree createTree(treeType val=0){
	void *tmpP = malloc(sizeof(treeNode));
	if (tmpP == NULL) return NULL;
	pTree pTr = (pTree)tmpP;
	pTr->decendent = pTr->sibling = NULL;
	pTr->val = val;
	return pTr;
}

//使用已经存在的树 创建
pTree createTree( pTree oldTree){  
	pTree pTr = createTree(0);
	copyTree(pTr, oldTree,TREE_DIRECTOR_SELF);
	return pTr;
}

//复制
bool copyTree(pTree pTr, pTree oldTree, int director = TREE_DIRECTOR_SELF){
	if (oldTree == NULL || pTr == NULL) return false;
	if (director == 0 && pTr->decendent != NULL) destoryTree(pTr->decendent);
	if (director == 1 && pTr->sibling != NULL) destoryTree(pTr->sibling);
	pTree pTrTmp = insertTree(pTr, oldTree->val, director);
	copyTree(pTrTmp, oldTree->sibling, TREE_DIRECTOR_SILING);
	copyTree(pTrTmp, oldTree->decendent, TREE_DIRECTOR_DECENDENT);
	return true;
}

//销毁
bool destoryTree(pTree &pTr){ 
	if (pTr==NULL) return false;
	destoryTree(pTr->decendent);
	destoryTree(pTr->sibling);
	free(pTr);
	pTr = NULL;
	return true;
}

//查找元素，返回子树
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

//节点追加,也可用于赋值
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

//批量追加节点
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

//节点删除
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

//获取父节点
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

//获取兄弟节点
pTree getSibling(pTree pTr, treeType val){
	pTree parentPTree = NULL;
	getParent(pTr, val, parentPTree);
	if (parentPTree == NULL) return NULL;
	return parentPTree->decendent;
}

//获取子树
pTree getDecendent(pTree pTr, treeType val){  
	pTree pTrTmp = locateTree(pTr, val,false);
	if (pTrTmp == NULL) return NULL;
	return pTrTmp->decendent;
}

//获取树深
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

//判断树是否为空
bool isEmptyTree(pTree pTr){ 
	if (pTr == NULL) return true;
	return pTr->decendent == NULL;
}

//遍历树
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


//创建
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