/*
* 树 测试
*
* author flybird1971@gmail.com
* since  2015-05-20
*/
#pragma once

#include"stdafx.h"
#include <stdio.h>
#include <iostream>
#include "tree_test.h"

using namespace std;

//普通树调试
void debugTree(){

	//创建树测试
	pTree pTr = createTree(12);
	pTree pTrTmp = NULL;
	pTrTmp = insertTree(pTr, 2, TREE_DIRECTOR_DECENDENT);
	pTree pTrTmp2 = insertTree(pTrTmp, 5, TREE_DIRECTOR_DECENDENT);
	pTrTmp2 = insertTree(pTrTmp2, 6, TREE_DIRECTOR_SILING);
	pTrTmp2 = insertTree(pTrTmp2, 7, TREE_DIRECTOR_SILING);

	pTrTmp = insertTree(pTrTmp, 3, TREE_DIRECTOR_SILING);
	pTrTmp = insertTree(pTrTmp, 4, TREE_DIRECTOR_SILING);
	traversalTree(pTr, dealF);
	cout << endl << endl;

	pTree pTrCopy = createTree(pTr);
	traversalTree(pTrCopy, dealF);
	cout << endl << endl;
	
	//树查找测试
	pTree subTree = locateTree(pTrCopy, 4,false);
	if (subTree == NULL){
		cout << "no exists...." << endl;
	}
	else{
		cout << "locate val is : " << subTree->val << endl;
	}
	
	/*subTree = locateTree(pTrCopy, 12, true);
	if (subTree == NULL){
		cout << "no exists...." << endl;
	}else{
		cout << "locate parent val is : " << subTree->val << endl;
	}*/

	//追加子叶
	pTree newLeaf = insertTree(subTree, 8, TREE_DIRECTOR_DECENDENT);
	newLeaf = insertTree(newLeaf, 9, TREE_DIRECTOR_SILING);
	insertTree(newLeaf, 10, TREE_DIRECTOR_DECENDENT);

	pTree subTree2 = locateTree(pTrCopy, 6, false);
	insertTree(subTree2, newLeaf, TREE_DIRECTOR_DECENDENT);
	traversalTree(pTrCopy, dealF);
	cout << endl << endl;
	
	//获取父节点，子节点，兄弟节点测试
	pTree parentNode = NULL;
	getParent(pTrCopy, 12, parentNode);
	if ( parentNode== NULL){
		cout << "获取父节点失败..." << endl;
	}else{
		cout << "父节点值 : " << parentNode->val << endl;
	}
	pTree siling =  getSibling(pTrCopy, 110);
	if (siling == NULL){
		cout << "获取兄弟点失败..." << endl;
	}
	else{
		cout << "第一个兄弟点值 : " << siling->val << endl;
	}
	
	pTree chird =  getDecendent(pTrCopy, 10);
	if (chird == NULL){
		cout << "获取子点失败..." << endl;
	}
	else{
		cout << "第一个子弟点值 : " << chird->val << endl;
	}

	//删除子树
	cout << "-------------------------------" << endl;
	deleteTree(pTrCopy, 4);
	traversalTree(pTrCopy, dealF);
	cout << endl << endl;

	//树深测试
	pTree pT1 = NULL;
	pTree pT2 = createTree(0);
	int depth = getTreeDepth(pT1);
	cout <<"depth is : "<< depth << endl;
	depth = getTreeDepth(pT2);
	cout << "depth is : " << depth << endl;
	depth = getTreeDepth(pTrCopy);
	cout << "depth is : " << depth << endl;

	//判断是否为空
	pTree tmpTree = createTree(0);
	pTree tmpTree2 = NULL;
	if (isEmptyTree(tmpTree2) == true){
		cout << "tree is empty.." << endl;
	}else{
		cout << "tree is not empty..." << endl;
	}

	destoryTree(pTr);
	destoryTree(pTrCopy);
}