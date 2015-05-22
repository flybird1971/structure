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

//����������
void debugBTree(){
	
	//����������
	pBTree pbTree = createBTree('A');
	cout << "----------------- create tree root  -------------------" << endl;
	traversalBTree(pbTree, dealBT, BIN_TREE_TRAVERSAL_PREORDER);

	//��������ʽ����������
	bTreeType val[31] = { 'A', 'B', 'C', 'D', '#', '#', 'H',
		'#', 'G', '#', '#', '#', '#', 'W', 'L', '#', '#', '#', '#', '#','#',
		'#', '#', '#', '#', '#', '#','M', '#', '#', '#' };
	pBTree pbTree2 = createBTree(val, 31, 1);  
	cout <<endl<< "----------------- array to bin tree -------------------" << endl;
	traversalBTree(pbTree2, dealBT, BIN_TREE_TRAVERSAL_PREORDER);

	//ʹ���Ѿ����ڵĶ����������д���
	pBTree pbTree3 = createBTree(pbTree2);   
	cout << endl << "----------------- tree to bin tree -------------------" << endl;
	traversalBTree(pbTree3, dealBT, BIN_TREE_TRAVERSAL_PREORDER);

	//��������
	pBTree pTmpBT = locateBTree(pbTree2, '0');
	pBTree newPos = insertBTree(pTmpBT, '2', BIN_TREE_DIRECTOR_RIGHT);   
	cout << endl << "----------------- tree to bin tree -------------------" << endl;
	traversalBTree(pTmpBT, dealBT, BIN_TREE_TRAVERSAL_PREORDER);
	if (newPos == NULL){
		cout << "��������ʧ��" << endl;
	}else{
		cout << "��������Ϊ : " << newPos->val << endl;
	}

	//��������
	pBTree pTmpBT2 = locateBTree(pbTree2,'D');
	pBTree pChird  = locateBTree(pbTree2, 'H');
	pBTree newPos2 = insertBTree(pTmpBT2, pChird, BIN_TREE_DIRECTOR_LEFT); 
	cout << endl << "----------------- tree to bin tree -------------------" << endl;
	traversalBTree(pTmpBT2, dealBT, BIN_TREE_TRAVERSAL_PREORDER); cout << endl;
	traversalBTree(pChird, dealBT, BIN_TREE_TRAVERSAL_PREORDER); cout << endl;
	traversalBTree(newPos2, dealBT, BIN_TREE_TRAVERSAL_PREORDER);
	if (newPos2 == NULL){
		cout << "��������ʧ��" << endl;
	}else{
		cout << "��������Ϊ : " << newPos2->val << endl;
	}

	//ɾ���ڵ�
	cout << endl << "----------------- before delete & bin tree -------------------" << endl;
	traversalBTree(pbTree3, dealBT, BIN_TREE_TRAVERSAL_PREORDER); cout << endl;
	if (deleteBTree(pbTree3, '0') == false){
		cout << "ɾ��ʧ��" << endl;
	}else{
		cout << "ɾ���ɹ� : " << endl;
	}
	cout << endl << "----------------- after delete & bin tree -------------------" << endl;
	traversalBTree(pbTree3, dealBT, BIN_TREE_TRAVERSAL_PREORDER); cout << endl;

	//��ȡ���ڵ�
	pBTree pParent =  getBTreeParent(pbTree3, 'B');     
	if (pParent == NULL){
		cout << "��ȡ���ڵ�ʧ��" << endl;
	}
	else{
		cout << "��ȡ���ڵ�Ϊ : " << pParent->val << endl;
	}

	//��ȡ�ֵܽڵ�
	pBTree pSiling = getBTreeSibling(pbTree3, 'B');
	if (pSiling == NULL){
		cout << "��ȡ�ֵܵ�ʧ��" << endl;
	}
	else{
		cout << "��ȡ�ֵܵ�Ϊ : " << pSiling->val << endl;
	}

	//��ȡ����
	pBTree pLeft = getBTreeLeftChird(pbTree3, 'B');
	if (pLeft == NULL){
		cout << "��ȡ����ʧ��" << endl;
	}
	else{
		cout << "��ȡ����Ϊ : " << pLeft->val << endl;
	}

	//��ȡ�Һ���
	pBTree pRight = getBTreeRightChird(pbTree3, 'B');
	if (pRight == NULL){
		cout << "��ȡ�Һ��ӵ�ʧ��" << endl;
	}
	else{
		cout << "��ȡ�Һ��ӵ�Ϊ : " << pRight->val << endl;
	}

	//��ȡ����
	deleteBTree(pbTree3, '0');
	int depth = getBTreeDepth(pbTree3);  
	cout << "tree depth is : " << depth << endl;
	
	//�ж��Ƿ�Ϊ��
	pBTree pt = NULL;
	if (isEmptyBTree(pt) == false){
		cout << "tree is  not empty " << endl;
	}else{
		cout << "tree is empty" << endl;
	}
	destoryBTree(pbTree);
	destoryBTree(pbTree2);
	destoryBTree(pbTree3);
}

//���Ҳ���ӡÿ��Ҷ�ӵ�·��
void findLeafPath(){
	//��������ʽ����������
	bTreeType val[31] = { 'A', 'B', 'C', 'D', '#', '#', 'H',
		'#', 'G', '#', '#', '#', '#', 'W', 'L', '#', '#', '#', '#', '#', '#',
		'#', '#', '#', '#', '#', '#', 'M', '#', '#', '#' };
	pBTree pbTree = createBTree(val, 31, 1);
	cout << endl << "----------------- array to bin tree -------------------" << endl;
	traversalBTree(pbTree, dealBT, BIN_TREE_TRAVERSAL_PREORDER);
	pBTree pTmp = locateBTree(pbTree, 'C');
	pBTree pInsert = locateBTree(pbTree, 'L');
	insertBTree(pInsert, pTmp, BIN_TREE_DIRECTOR_LEFT);
	traversalBTree(pbTree, dealBT, BIN_TREE_TRAVERSAL_PREORDER);

	stack Stack;
	initStack(Stack);
	cout << endl;
	traversalBTree(pbTree, dealBTreeEx, BIN_TREE_TRAVERSAL_PREORDER,Stack);
}

void haffmanTree(){
	huffman pHuffm[9] = {};
	pHuffm[0].weight = 10; pHuffm[0].val = 'A';		pHuffm[1].weight = 2;  pHuffm[1].val = 'B';
	pHuffm[2].weight = 8;  pHuffm[2].val = 'C';		pHuffm[3].weight = 5;  pHuffm[3].val = 'D';
	pHuffm[4].weight = 15; pHuffm[4].val = 'E';		pHuffm[5].weight = 20; pHuffm[5].val = 'F';
	pHuffm[6].weight = 1;  pHuffm[6].val = 'G';		pHuffm[7].weight = 4;  pHuffm[7].val = 'H';
	pHuffm[8].weight = 7;  pHuffm[8].val = 'I';
	pHuffman huffmTree = initHuffman(pHuffm, 9);
	
	codeMap map = {};
	show(huffmTree);
	int root = findHuffmanTreeRoot(huffmTree);
	getPath(huffmTree, root, dealHuffman, map);
	cout << "--------------------------------------------------" << endl;
	printArr(map,MAX_BUFFER);
	cout << "--------------------------------------------------" << endl;
	string val;
	string code = "000011011111";
	decode(huffmTree, root,root, code, val);
	cout << "decode 000 is " << val << endl;
	destoryHuffman(huffmTree);
}

//���������ܣ�����,ѹ��
void haffmanEcode(){
	//int count = 0;
	//pHuffman pHuffm = countFrequncy("ReadMe.txt",count);
	//printBasicDatas(pHuffm, count);
	//pHuffm = initHuffman(pHuffm, count);
	//cout << "**********************************************" << endl;
	//show(pHuffm);
	
	//cout << "**********************************************" << endl;
	//codeMap map = {};
	//int root = findHuffmanTreeRoot(pHuffm);
	//getPath(pHuffm, root, dealHuffman, map);
	//printArr(map,MAX_BUFFER);

	if (compress("ReadMe.txt", "readme.lxg") == false) cout << "ʧ��...." << endl;
	cout << "ok" << endl;

	if (uncompress("readme.lxg","uncompress.txt") == false) cout << "ʧ��...." << endl;
	cout << "ok" << endl;
}

void printArr(codeMap map, int length){
	char tmp = '\0';
	for (int i = 0; i < length; i++){
		tmp = i;
		cout << tmp << " huffman code is  : " << map[i] << endl;
	}
}

bool printBasicDatas(pHuffman pHuffm,int length){
	if (pHuffm == NULL) return false;
	for (int i = 0; i < length; i++){
		cout << "index : " << i << "\tval : " << pHuffm[i].val << "\tweight : " << pHuffm[i].weight << "\tleftChrid : "
			<< pHuffm[i].leftChird << "\trightChird : " << pHuffm[i].rightChird << "\tparentNode : "
			<< pHuffm[i].parentNode << endl;//*/
	}
	return true;
}

