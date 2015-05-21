/*
* 数组实现 最优二叉树二叉树
*
* author flybird1971@gmail.com
* since  2015-05-21
*/

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include "stack.h"
#include "circle_queue.h"
#include<stdio.h>

const int DYNAMIC_ADD_STEP = 20;
const int MAX_WEIGHT = 100000;
const int MAP_LENGTH = 128;
const int MAX_BUFFER = 1000;

//哈弗曼树 节点定义
typedef  struct huffman_node{
	int   weight;
	char  val;
	int   leftChird;
	int   rightChird;
	int   parentNode;
}huffman,*pHuffman;

typedef string*  codeMap;

//********************* 基本操作 ***********************
pHuffman initHuffman(pHuffman pHuffm, int length);

bool createHuffman(pHuffman pHuffm,int length,int &size);

bool destoryHuffman(pHuffman &pHuffm);

bool uncompress(const char* inFile, const char* outFile);

//get path
bool getPath(pHuffman pHuffm, codeMap &map, stack &Stack);
bool recoverInfos(pHuffman pHuffm, FILE* &inHandle, FILE* &outHnadle);
pHuffman readHeaderInfos(FILE* &inHandle, int &length);
//get two min ele
void getTwoMin(pHuffman pHuffm, int length, int &lastIndex, int &secondIndex);


