/*
* 二叉树
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

//定义树节点
typedef struct bin_tree_node{
	bTreeType val;
	bin_tree_node* leftChird;
	bin_tree_node* rightChird;
}bTreeNode, *pBTreeNode, bTree, *pBTree;

typedef void(*dealBTree)(bTreeType &);
typedef void(*dealBTEx)(pBTree , stack &);


//********************* 基本操作 ***********************
pBTree createBTree(bTreeType dataArr[], int length, int index);  //以数组形式创建二叉树
pBTree createBTree(bTreeType val);    //创建只含根的二叉树
pBTree createBTree(pBTree oldTree);   //使用已经存在的二叉树，进行创建
bool destoryBTree(pBTree &pTr);       //销毁二叉树

pBTree locateBTree(pBTree pTr, bTreeType val);                //查找
pBTree insertBTree(pBTree pTr, bTreeType val, int dirctor);   //插入数据
pBTree insertBTree(pBTree pTr, pBTree decedent, int dirctor); //插入子树
bool deleteBTree(pBTree pTr, bTreeType val);                  //删除节点

pBTree getBTreeParent(pBTree pTr, bTreeType val);     //获取父节点
pBTree getBTreeSibling(pBTree pTr, bTreeType val);    //获取兄弟节点
pBTree getBTreeLeftChird(pBTree pTr, bTreeType val);  //获取左孩子
pBTree getBTreeRightChird(pBTree pTr, bTreeType val); //获取右孩子

int  getBTreeDepth(pBTree pTr);  //获取树深
bool isEmptyBTree(pBTree pTr);   //判断是否为空

void dealBT(bTreeType &val);            //遍历处理器
void dealBTreeEx(pBTree pTr, stack &Stack);//遍历处理器
bool traversalBTree(pBTree pTr, dealBTree dealBTS, int order); //前序遍历 中序遍历 后序遍历
bool traversalBTree(pBTree pTr, dealBTEx dealBTreeEx, int order, stack &Stack);