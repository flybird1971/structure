/*
* �� ����
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

//��ͨ������
void debugTree(){

	//����������
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
	
	//�����Ҳ���
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

	//׷����Ҷ
	pTree newLeaf = insertTree(subTree, 8, TREE_DIRECTOR_DECENDENT);
	newLeaf = insertTree(newLeaf, 9, TREE_DIRECTOR_SILING);
	insertTree(newLeaf, 10, TREE_DIRECTOR_DECENDENT);

	pTree subTree2 = locateTree(pTrCopy, 6, false);
	insertTree(subTree2, newLeaf, TREE_DIRECTOR_DECENDENT);
	traversalTree(pTrCopy, dealF);
	cout << endl << endl;
	
	//��ȡ���ڵ㣬�ӽڵ㣬�ֵܽڵ����
	pTree parentNode = NULL;
	getParent(pTrCopy, 12, parentNode);
	if ( parentNode== NULL){
		cout << "��ȡ���ڵ�ʧ��..." << endl;
	}else{
		cout << "���ڵ�ֵ : " << parentNode->val << endl;
	}
	pTree siling =  getSibling(pTrCopy, 110);
	if (siling == NULL){
		cout << "��ȡ�ֵܵ�ʧ��..." << endl;
	}
	else{
		cout << "��һ���ֵܵ�ֵ : " << siling->val << endl;
	}
	
	pTree chird =  getDecendent(pTrCopy, 10);
	if (chird == NULL){
		cout << "��ȡ�ӵ�ʧ��..." << endl;
	}
	else{
		cout << "��һ���ӵܵ�ֵ : " << chird->val << endl;
	}

	//ɾ������
	cout << "-------------------------------" << endl;
	deleteTree(pTrCopy, 4);
	traversalTree(pTrCopy, dealF);
	cout << endl << endl;

	//�������
	pTree pT1 = NULL;
	pTree pT2 = createTree(0);
	int depth = getTreeDepth(pT1);
	cout <<"depth is : "<< depth << endl;
	depth = getTreeDepth(pT2);
	cout << "depth is : " << depth << endl;
	depth = getTreeDepth(pTrCopy);
	cout << "depth is : " << depth << endl;

	//�ж��Ƿ�Ϊ��
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