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
#include "tree_test.h"

using namespace std;

//********************* 基本操作 ***********************
pHuffman initHuffman(pHuffman pHuffm, int length){
	void * pTmp = malloc(sizeof(huffman)*(length + DYNAMIC_ADD_STEP));
	if (pTmp == NULL) return NULL;
	pHuffman pRes = (pHuffman)pTmp;
	for (int i = 0; i < length; i++){
		pRes[i].val        = pHuffm[i].val;
		pRes[i].weight     = pHuffm[i].weight;
		pRes[i].leftChird  = -1;
		pRes[i].rightChird = -1;
		pRes[i].parentNode = -1;
	}
	if (createHuffman(pRes, length, DYNAMIC_ADD_STEP, length + DYNAMIC_ADD_STEP) == false) cout << "fail.." << endl;
	return pRes;
}

bool createHuffman(pHuffman &pHuffm, int length, int allowUseSize,int size){
	if (pHuffm == NULL||length<1) return false;
	if (length == 1) return true;
	if (allowUseSize == 0){
		size = size + DYNAMIC_ADD_STEP;
		allowUseSize = DYNAMIC_ADD_STEP;
		void *pTmp = realloc(pHuffm, size*sizeof(huffman));
		if (pTmp == NULL) return false;
		pHuffm = (pHuffman)pTmp;
	}
	int last = -1;
	int second = -1;
	getMin(pHuffm,length, last);
	if (last == -1) return false;
	pHuffm[last].parentNode = -2;
	getMin(pHuffm, length-1, second);
	if (second == -1) return false;
	pHuffm[second].parentNode = -2;

	int weight = pHuffm[last].weight + pHuffm[second].weight;
	int index = size - allowUseSize;
	pHuffm[index].val        = '\0';
	pHuffm[index].weight     = weight;
	pHuffm[index].leftChird  = last;
	pHuffm[index].rightChird = second;
	pHuffm[index].parentNode = -1;
	
	pHuffm[last].parentNode   = index;
	pHuffm[second].parentNode = index;
	if (createHuffman(pHuffm, length - 1, allowUseSize - 1, size) == true) return true;
	return false;
}

//get two min ele
void getMin(pHuffman pHuffm, int length, int &lastIndex){
	int  lastWeight;
	lastWeight = MAX_WEIGHT;
	int index = 0;
	while (length > 0){
		if (pHuffm[index].parentNode != -1){
			index++;
			continue;
		}
		lastWeight = lastWeight >= pHuffm[index].weight ? pHuffm[index].weight : lastWeight;
		lastIndex = lastWeight >= pHuffm[index].weight ? index : lastIndex;
		length--;
		index++;
	}
}

bool destoryHuffman(pHuffman &pHuffm){
	if (pHuffm == NULL) return true;
	free(pHuffm);
	pHuffm = NULL;
	return true;
}

//*********************** 压缩文件 *******************************//
bool compress(const char* inFile, const char* outFile){
	FILE* inHandle, *outHandle;
	fopen_s(&inHandle, inFile, "rb"); 
	fopen_s(&outHandle, outFile, "w+");
	if (inHandle == NULL || outHandle == NULL) return false;

	//写头信息
	int count = 0;
	pHuffman pHuffm = countFrequncy(inFile, count);
	int offset = count*sizeof(huffman);
	fwrite(&offset, sizeof(int), 1, outHandle);
	fwrite((char*)pHuffm, sizeof(char), offset, outHandle);
	
	codeMap map;
	pHuffm = initHuffman(pHuffm, count); //生成哈弗曼树
	int root = findHuffmanTreeRoot(pHuffm);
	getPath(pHuffm, root, dealHuffman, map); //生成编码
	compressInfos(map, inHandle, outHandle); //压缩文件

	fclose(inHandle);
	fclose(outHandle);
	return true;
}

bool compressInfos(codeMap &map, FILE* &inHandle, FILE* &outHnadle){
	int num, index, tmpNum,i;
	num = index = tmpNum = 0;
	char buff[MAX_BUFFER];
	char str[MAX_BUFFER] = {""};
	string tmp;
	fseek(inHandle, 0, SEEK_CUR);
	while (num = fread(buff, sizeof(char), MAX_BUFFER, inHandle) != 0){
		i = 0;
		while ( i<MAX_BUFFER){
			tmpNum = 0;
			tmp = map[buff[i]];
			while (tmp[tmpNum] != '\0'){
				str[index/8] = str[index/8] | ( (tmp[tmpNum]-'0')<<(index%8) );
				index++; tmpNum++;
				if (index == MAX_BUFFER * 8){
					if (fwrite(str, sizeof(char), MAX_BUFFER, outHnadle) != MAX_BUFFER) return false;
					index = 0;
				}
			}
			i++;
		}
		num = 0;
		fseek(inHandle, 0, SEEK_CUR);
	}

	if(index != 0){
		if (fwrite(str, sizeof(char), (index+8)/8, outHnadle) != (index+8)/8) return false;
	}
	return true;
}

//get path
bool getPath(pHuffman pHuffm, int root, dealHufman dealF, codeMap map){
	if (pHuffm == NULL || root==-1 || map==NULL) return false;
	dealF(pHuffm, root, map);
	getPath(pHuffm, pHuffm[root].leftChird, dealF, map);
	getPath(pHuffm, pHuffm[root].rightChird, dealF, map);
	return true;
}

//读取文件，统计字符频率
pHuffman countFrequncy(const char* inFile,int &length){
	FILE* inHandle;
	fopen_s(&inHandle, inFile, "r");
	if (inHandle == NULL) return NULL;
	void* pTmp = malloc(sizeof(huffman)*MAP_LENGTH);
	if (pTmp == NULL) return NULL;
	pHuffman pHuffm = (pHuffman)pTmp;
	for (int i = 0; i < MAP_LENGTH; i++){
		pHuffm[i].leftChird = pHuffm[i].rightChird = pHuffm[i].parentNode = -1;
		pHuffm[i].val = i;
		pHuffm[i].weight = 0;
	}
	
	int index = 0;
	int num = 0;
	char buffer[MAX_BUFFER] = {"aa"};
	cout << "*****************************************************" << endl;
	while (num = fread(buffer, sizeof(char), MAX_BUFFER, inHandle) != 0){
		while (index < MAX_BUFFER){
			//cout << buffer[index];
			pHuffm[buffer[index++]].weight++;
		}
		index = num = 0;
	}
	cout << "\n*****************************************************\n";
	fclose(inHandle);
	pHuffm = compactMap(pHuffm, length); //将频率为空字符删除
	return pHuffm;
}

//*********************** 解压缩 *******************************//
bool uncompress(const char* inFile, const char* outFile){
	int length = 0;
	FILE* inHandle, *outHnadle;
	fopen_s(&inHandle, inFile, "rb");  
	fopen_s(&outHnadle, outFile, "w+"); 
	if (inHandle == NULL || outHnadle == NULL) return false;

	pHuffman pHuffm = readHeaderInfos(inHandle, length);
	cout << "length : " << length << endl;
	printBasicDatas(pHuffm, length);
	//pHuffm = initHuffman(pHuffm, length);
	//if (recoverInfos(pHuffm, inHandle, outHnadle) == false) return false;
	fclose(inHandle);
	fclose(outHnadle);
	return true;
}

//读取文件头信息 生成原始数据，用于生成哈弗曼树
pHuffman readHeaderInfos(FILE* &inHandle, int &length){
	if (fread(&length, sizeof(int), 1, inHandle) == 0) return NULL;
	void *pTmp = malloc(length);
	if (pTmp == NULL) return NULL;
	char* buffer = (char*)pTmp;
	if (fread(buffer, sizeof(char), length, inHandle) == 0) return NULL;
	pHuffman pRes = (pHuffman)buffer;
	cout << "weight :　" << pRes[10].weight << "\tval : " << pRes[10].val
		<< "\tleftchird : " << pRes[10].leftChird << endl;
	length = length / sizeof(huffman);
	return pRes;
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

//精简code map
pHuffman compactMap(pHuffman pHuffm, int &length){
	if (pHuffm == NULL) return NULL;
	int count = 0;
	for (int i = 0; i < MAP_LENGTH; i++){
		if (pHuffm[i].weight > 0) count++;
	}
	void *pTmp = malloc(sizeof(huffman)*count);
	if (pTmp == NULL){
		free(pHuffm);
		return NULL;
	}
	length = count;
	int index = 0;
	pHuffman pRes = (pHuffman)pTmp;
	for (int i = 0; i < MAP_LENGTH; i++){
		if (pHuffm[i].weight > 0){
			pRes[index].val = pHuffm[i].val;
			pRes[index].weight = pHuffm[i].weight;
			pRes[index].leftChird = pHuffm[i].leftChird;
			pRes[index].rightChird = pHuffm[i].rightChird;
			pRes[index++].parentNode = pHuffm[i].parentNode;
		}
	}
	free(pHuffm);
	return pRes;
}

void show(pHuffman pHuffm){
	int i = 0;
	int count = 0;
	while (pHuffm[i].parentNode != -1){
		cout <<"index : "<<i<< "\tval : " << pHuffm[i].val << "\tweight : " << pHuffm[i].weight << "\tleftChrid : "
			<< pHuffm[i].leftChird << "\trightChird : " << pHuffm[i].rightChird << "\tparentNode : "
			<< pHuffm[i].parentNode << endl;
		count += pHuffm[i].weight;
		i++;
	}
	cout <<"index : "<<i <<"\tval : " << pHuffm[i].val << "\tweight : " << pHuffm[i].weight << "\tleftChrid : "
		<< pHuffm[i].leftChird << "\trightChird : " << pHuffm[i].rightChird << "\tparentNode : "
		<< pHuffm[i].parentNode << endl;
	count += pHuffm[i].weight;
	cout << "total char is : " << count << endl;
}

int findHuffmanTreeRoot(pHuffman pHuffm){
	if (pHuffm == NULL) return -1;
	int index = 0;
	while (pHuffm[index].parentNode != -1){
		index++;
	}
	return index;
}

void dealHuffman(pHuffman pHuffm,int offset,codeMap map){
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
}

//解析编码
bool decode(pHuffman pHuffm, int root,int currentIndex, string code,string &val){
	if (pHuffm == NULL || root == -1 || currentIndex==-1) return false;

	int index = 0;
	while (code[index] != '\0'){
		if (code[index] == '0') currentIndex = pHuffm[currentIndex].leftChird;
		if (code[index] == '1') currentIndex = pHuffm[currentIndex].rightChird;
		if (pHuffm[currentIndex].leftChird == -1 && pHuffm[currentIndex].rightChird == -1){
			val += pHuffm[currentIndex].val;
			currentIndex = root;
		}
		index++;
	}
	return true;
}