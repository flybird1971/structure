/*
* �� ����
*
* author flybird1971@gmail.com
* since  2015-05-20
*/
#pragma once
#include <stdio.h>
#include "error_code.h"
#include "tree.h"
#include "bTree.h"
#include "stack.h"
#include "huffman_tree.h"

void debugTree();   //��ͨ������
void debugBTree();  //����������

void findLeafPath();   //���Ҳ���ӡÿ��Ҷ�ӵ�·��

void printArr(codeMap map, int length);
void haffmanTree();  //��������
void haffmanEcode(); //���������ܣ�����,ѹ��
bool printBasicDatas(pHuffman pHuffm, int length);