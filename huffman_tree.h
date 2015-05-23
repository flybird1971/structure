/*
* ����ʵ�� ���Ŷ�����������
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

using namespace std;

const int DYNAMIC_ADD_STEP = 20;
const int MAX_WEIGHT = 100000;
const int MAP_LENGTH = 128;
const int MAX_BUFFER = 100;

//�������� �ڵ㶨��
typedef  struct huffman_node{
	int   weight;
	char  val;
	int   leftChird;
	int   rightChird;
	int   parentNode;
}huffman,*pHuffman;

typedef string(codeMap)[MAP_LENGTH];
typedef void(*dealHufman)(pHuffman, int, codeMap);

//********************* �������� ***********************
pHuffman initHuffman(pHuffman pHuffm, int length);
bool createHuffman(pHuffman &pHuffm, int length, int allowUseSize, int size);
void getMin(pHuffman pHuffm, int length, int &lastIndex);
bool destoryHuffman(pHuffman &pHuffm);
int findHuffmanTreeRoot(pHuffman pHuffm);

pHuffman readHeaderInfos(FILE* &inHandle, int &length);
bool uncompress(const char* inFile, const char* outFile);
bool recoverInfos(pHuffman pHuffm, FILE* &inHandle, FILE* &outHnadle);

pHuffman countFrequncy(const char* inFile, int &length);
bool compress(const char* inFile, const char* outFile);
bool getPath(pHuffman pHuffm, int offset, dealHufman dealF, codeMap map);
bool compressInfos(codeMap &map, FILE* &inHandle, FILE* &outHnadle);
void dealHuffman(pHuffman pHuffm, int offset, codeMap map);

void show(pHuffman pHuffm);
pHuffman compactMap(pHuffman pHuffm, int &length);
bool decode(pHuffman pHuffm, int root, string code, string &val, int &length);
