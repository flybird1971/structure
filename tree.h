/*
* 树
*
* author flybird1971@gmail.com
* since  2015-05-19
*/

#pragma once

#include <stdio.h>
#include <iostream>

const int TREE_DIRECTOR_DECENDENT = 0;
const int TREE_DIRECTOR_SILING    = 1;
const int TREE_DIRECTOR_SELF      = -1;
typedef int treeType;

//定义树节点
typedef struct tree_node{
	treeType val;
	tree_node* sibling;
	tree_node* decendent;
}treeNode, *pTreeNode, tree, *pTree;

typedef void(*dealTree)(treeType &);

//********************* 基本操作 ***********************
pTree createTree(pTree oldTree);
pTree createTree(treeType val);
bool copyTree(pTree pTr, pTree oldTree, int director );
bool destoryTree(pTree &pTr);

pTree locateTree(pTree pTr, treeType val, bool getPrevious );
pTree insertTree(pTree pTr, treeType val, int dirctor);
pTree insertTree(pTree pTr, pTree decedent, int dirctor);
bool deleteTree(pTree pTr, treeType val);

bool getParent(pTree pTr, treeType val, pTree &parentNode);
pTree getSibling(pTree pTr, treeType val);
pTree getDecendent(pTree pTr, treeType val);
int  getTreeDepth(pTree pTr);

bool isEmptyTree(pTree pTr);
bool traversalTree(pTree pTr, dealTree dealF);
void dealF(treeType &val);
