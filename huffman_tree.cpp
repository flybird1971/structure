/*
* 数组实现 最优二叉树二叉树
*
* author flybird1971@gmail.com
* since  2015-05-21
*/
#pragma once

#include"stdafx.h"
#include "error_code.h"
#include <iostream>
#include "huffman_tree.h"

using namespace std;

//********************* 基本操作 ***********************
pHuffman initHuffman(pHuffman pHuffm, int length){
	void * pTmp = malloc(sizeof(huffman)*(length + DYNAMIC_ADD_STEP));
	if (pTmp == NULL) return NULL;
	pHuffman pRes = (pHuffman)pTmp;
	for (int i = 0; i < length; i++){
		pRes[i].val        = pHuffm[i].val;
		pRes[i].weight     = pHuffm[i].weight;
		pRes[i].leftChird  = pHuffm[i].leftChird;
		pRes[i].rightChird = pHuffm[i].rightChird;
		pRes[i].parentNode = pHuffm[i].parentNode;
	}
	createHuffman(pRes, length, DYNAMIC_ADD_STEP, length + DYNAMIC_ADD_STEP);
	return pRes;
}

bool createHuffman(pHuffman pHuffm, int length, int allowUseSize,int size){
	if (pHuffm == NULL||length<1) return false;
	if (length == 1) return true;
	if (allowUseSize == 0){
		void *pTmp = realloc(pHuffm, size + DYNAMIC_ADD_STEP);
		if (pTmp == NULL) return false;
		pHuffm = (pHuffman)pTmp;
	}
	int last = -1;
	int second = -1;
	getTwoMin(pHuffm,length, last, second);
	if (last == -1 || second == -1) return false;

	int weight = pHuffm[last].weight + pHuffm[second].weight;
	int index = size - allowUseSize;
	pHuffm[index].val        = '\0';
	pHuffm[index].weight     = weight;
	pHuffm[index].leftChird  = last;
	pHuffm[index].rightChird = second;
	pHuffm[index].parentNode = -1;
	
	pHuffm[last].parentNode   = index;
	pHuffm[second].parentNode = index;

	if (createHuffman(pHuffm, length - 1, allowUseSize - 1, size + 1) == true) return true;
	return false;
}

bool destoryHuffman(pHuffman &pHuffm){
	if (pHuffm == NULL) return true;
	free(pHuffm);
	pHuffm = NULL;
	return true;
}

//解压缩
bool uncompress(const char* inFile, const char* outFile){
	int length = 0;
	FILE* inHandle  = fopen(inFile, "rb");
	FILE* outHnadle = fopen(outFile, "a+");
	if (inHandle == NULL || outHnadle == NULL) return false;
	pHuffman pHuffm = readHeaderInfos(inHandle, length);
	pHuffman pHuffm = initHuffman(pHuffm, length);
	if (recoverInfos(pHuffm,inHandle,outHnadle) == false) return false;
	fclose(inHandle);
	fclose(outHnadle);
	return true;
}

//恢复压缩信息
bool recoverInfos(pHuffman pHuffm, FILE* &inHandle, FILE* &outHnadle){
	int indexRes;
	int num = 0;
	char buff[MAX_BUFFER * 8];
	char str[MAX_BUFFER];
	pHuffman pTmp = pHuffm;
	while (num = fread(buff, 1, MAX_BUFFER * 8, inHandle) != 0){
		int i = 0;
		indexRes = 0;
		while (i < num){
			if (buff[i] == 0) pTmp = pHuffm + pHuffm->leftChird;
			if (buff[i] == 1) pTmp = pHuffm + pHuffm->rightChird;
			if (pTmp->leftChird == -1 && pTmp->rightChird == -1){
				str[indexRes++] = pTmp->val;
				if (indexRes == MAX_BUFFER){
					if (fwrite(str, sizeof(char), MAX_BUFFER, outHnadle) != MAX_BUFFER) return false;
					indexRes = 0;
				}
				pTmp = pHuffm;
			}
			i++;
		}
		num = 0;
	}

	if (indexRes != 0){
		if (fwrite(str, sizeof(char), indexRes, outHnadle) != indexRes) return false;
	}
	return true;
}

//读取文件头信息 生成原始数据，用于生成哈弗曼树
pHuffman readHeaderInfos(FILE* &inHandle, int &length){
	int* pBuffer;
	if (fread(pBuffer, sizeof(int), 1, inHandle) != 1) return NULL;
	length = *pBuffer;
	char* buffer;
	if (fread(buffer, sizeof(char), length, inHandle) != length) return NULL;
	fclose(inHandle);
	pHuffman pRes = (pHuffman)buffer;
	return pRes;
}

//get path
bool getPath(pHuffman pHuffm,int offset, codeMap &map){
	if (pHuffm == NULL || offset==-1) return false;
	if (map == NULL){
		void *pTmp = malloc(sizeof(int)*MAP_LENGTH);
		if (pTmp == NULL) return false;
		map = (string*)pTmp;
	}

	if (pHuffm[offset].leftChird == -1 && pHuffm[offset].rightChird == -1){
		int index = offset;
		while (pHuffm[index].parentNode != -1){
			if (pHuffm[pHuffm[index].parentNode].leftChird == index) 
				map[pHuffm[offset].val] = '0' + map[pHuffm[offset].val];
			if (pHuffm[pHuffm[index].parentNode].rightChird == index) 
				map[pHuffm[offset].val] = '1' + map[pHuffm[offset].val];
			index = pHuffm[index].parentNode;
		}
	}

	getPath(pHuffm, pHuffm[offset].leftChird, map);
	getPath(pHuffm, pHuffm[offset].rightChird, map);
	return true;
}

//get two min ele
void getTwoMin(pHuffman pHuffm,int length ,int &lastIndex, int &secondIndex){
	int  lastWeight ,secondWeight;
	lastWeight = secondWeight = MAX_WEIGHT;
	int index = 0;
	while (length > 0){
		if (pHuffm[index].parentNode == -1){
			index++;
			continue;
		}
		secondWeight = lastWeight < pHuffm[index].weight && secondWeight > pHuffm[index].weight 
						? pHuffm[index].weight : secondWeight;
		secondIndex = lastWeight < pHuffm[index].weight && secondWeight > pHuffm[index].weight
			? index : secondIndex;
		lastWeight = lastWeight > pHuffm[index].weight ? pHuffm[index].weight : lastWeight;
		lastIndex = lastWeight > pHuffm[index].weight ? index : lastIndex;
		length--;
		index++;
	}
}


//读取文件，统计字符频率
pHuffman countFrequncy(const char* inFile){
	FILE* inHandle = fopen(inFile, "r");
	if (inHandle == NULL) return NULL;
	void* pTmp = malloc(sizeof(huffman)*MAP_LENGTH);
	if (pTmp == NULL) return NULL;
	pHuffman pHuffm = (pHuffman)pTmp;
	for (int i = 0; i < MAP_LENGTH; i++){
		pHuffm[i].leftChird = pHuffm[i].rightChird = pHuffm[i].parentNode -1;
		pHuffm[i].val = i;
		pHuffm[i].weight = 0;
	}
	
	int index, num;
	index = num = 0;
	char buffer[MAX_BUFFER];
	while (num = fread(buffer, sizeof(char), MAX_BUFFER, inHandle) != 0){
		while (index < num){
			pHuffm[buffer[index++]].weight++;
		}
		index = num = 0;
	}
	fclose(inHandle);
	return pHuffm;
}

//压缩文件
bool compress(const char* inFile, const char* outFile){
	int length = MAP_LENGTH;
	FILE* inHandle = fopen(inFile, "rb");
	FILE* outHnadle = fopen(outFile, "a+");
	if (inHandle == NULL || outHnadle == NULL) return false;
	
	//写头信息
	pHuffman pHuffm = countFrequncy(inFile);
	int offset = length*sizeof(huffman);
	fwrite(&offset, sizeof(int), 1, outHnadle);
	fwrite(pHuffm, sizeof(char), offset, outHnadle);

	codeMap map;
	pHuffman pHuffm = initHuffman(pHuffm, length); //生成哈弗曼树
	getPath(pHuffm,0,map); //生成编码
	compressInfos(map,inHandle,outHnadle); //压缩文件
    
	fclose(inHandle);
	fclose(outHnadle);
	return true;
}

bool compressInfos(codeMap &map, FILE* &inHandle, FILE* &outHnadle){
	int num, index, tmpNum;
	num = index = tmpNum = 0;
	char buff[MAX_BUFFER];
	char str[MAX_BUFFER*8];
	while (num = fread(buff, sizeof(char), MAX_BUFFER, inHandle) != 0){
		int i = 0;
		while (i < num){
		   string t = map[buff[i]];
		   //写入str中..
		   if (index == MAX_BUFFER * 8){
			   if (fwrite(str, sizeof(char), MAX_BUFFER, outHnadle) != MAX_BUFFER) return false;
			   index = 0;
		   }
		   i++;
		}
		num = 0;
	}
	return true;
}
