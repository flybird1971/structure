/*
* 矩阵表示及常见矩阵运算
*
* author flybird1971@gmail.com
* since  2015-05-17
*/

#pragma once

#include"stdafx.h"
#include "error_code.h"
#include <iostream>
#include <stdlib.h>
#include "matrixEx.h"

using namespace std;

//初始化
bool initMatrix(matrix &matr, unsigned rows, unsigned cols){
	void *tmpP = malloc(sizeof(eleMatrixType)*rows*cols);
	if (tmpP == NULL) return false;
	matr.val = (eleMatrixType*)tmpP;
	matr.cols = cols;
	matr.rows = rows;
	return true;
}

bool destoryMatrix(matrix &matr){
	if (matr.val == NULL) return false;
	free(matr.val);
	matr.val = NULL;
	matr.cols = 0;
	matr.rows = 0;
	return true;
}

bool assignMatrix(matrix &matr, eleMatrixType val[], int length){
	if (length != matr.rows*matr.cols) return false;
	for (int i = 0; i < length; i++){
		matr.val[i] = val[i];
	}
	return true;
}

bool assignMatrix(matrix &matr, matrix val){
	if (matr.cols != val.cols || matr.rows != val.rows) return false;
	int length = matr.cols*matr.rows;
	for (int i = 0; i < length; i++){
		matr.val[i] = val.val[i];
	}
	return true;
}

bool subtractMatrix(matrix  minuend, matrix subtract, matrix &result){ //减法
	if (minuend.rows != subtract.rows || minuend.cols != subtract.cols) return false;
	if (result.val == NULL || result.rows != minuend.rows || result.cols != minuend.cols) return false;
	int index = 0;
	for (int i = 0; i < minuend.rows; i++){
		for (int j = 0; j < minuend.cols; j++){
			index = i*minuend.cols + j;
			result.val[index] = minuend.val[index] - subtract.val[index];
		}
	}
	return true;
}

bool plusMatrix(matrix plused, matrix plus, matrix &result){ //加法
	if (plused.rows != plus.rows || plused.cols != plus.cols) return false;
	if (result.val == NULL || result.rows != plused.rows || result.cols != plused.cols) return false;
	int index = 0;
	for (int i = 0; i < plused.rows; i++){
		for (int j = 0; j < plused.cols; j++){
			index = i*plused.cols + j;
			result.val[index] = plused.val[index] + plus.val[index];
		}
	}
	return true;
}

bool multiplicationMatrix(matrix multipled, matrix multiple, matrix &result){ //乘法
	if (multipled.cols != multiple.rows) return false;
	if (result.val == NULL || result.rows != multipled.rows || result.cols != multiple.cols) return false;
	for (int i = 0; i < multipled.rows; i++){
		for (int j = 0; j < multiple.cols; j++){
			result.val[i*result.cols + j] = 0;
			for (int k = 0; k < multiple.rows; k++){
				result.val[i*result.cols + j] += multipled.val[i*multipled.cols + k] * multiple.val[k*multiple.cols + j];
			}
		}
	}
	return true;
}

bool transposeMatrix(matrix val, matrix &result){ //转置
	if (val.cols != result.rows || val.rows != result.cols) return false;
	int length = val.rows*val.cols;
	int rows, cols, newIndex;
	for (int i = 0; i < length; i++){
		rows = i / val.cols;
		cols = i%val.cols;
		newIndex = cols*result.cols + rows;
		result.val[newIndex] = val.val[i];
	}
	return true;
}

bool showMatrix(matrix matr){
	int length = matr.cols*matr.rows;
	if (matr.val==NULL){
		cout << "矩阵已销毁，打印失败"<<endl;
		return false;
	}
	if (length == 0){
		cout << "矩阵为空，打印失败" << endl;
		return false;
	}
	for (int i = 0; i < length; i++){
		cout << matr.val[i] << "\t";
		if ((i + 1) % matr.cols == 0) cout << endl;
	}
	cout << "\n\n";
	return true;
}

/* ---------------------------- 稀疏矩阵 操作 ---------------------------------*/
bool initSparseMatrix(sparseMatrix &matr){
	matr.val = NULL;
	matr.size = matr.rows = matr.cols = 0;
	return true;
}

bool destorySparseMatrix(sparseMatrix &matr){
	if (matr.val != NULL){
		free(matr.val);
		matr.val = NULL;
		matr.size = matr.cols = matr.rows = 0;
	}
	return true;
}

bool assignSparseMatrix(sparseMatrix &matr, int(*val)[3], int length, int rows, int cols){
	if (matr.val != NULL) free(matr.val);
	void * tmpP = malloc(sizeof(int) * 3 * length);
	if (tmpP == NULL) return false;
	matr.val = (int(*)[3])tmpP;
	matr.size = length;
	matr.rows = rows;
	matr.cols = cols;
	for (int i = 0; i < length; i++){
		matr.val[i][0] = val[i][0];
		matr.val[i][1] = val[i][1];
		matr.val[i][2] = val[i][2];
	}
	return true;
}

bool assignSparseMatrix(sparseMatrix &matr, sparseMatrix val){
	if (val.size <= 0 || val.val == NULL) return false;
	if (matr.val != NULL) free(matr.val);
	matr.size = val.size;
	matr.cols = val.cols;
	matr.rows = val.rows;
	void * tmpP = malloc(sizeof(int) * 3 * val.size);
	if (tmpP == NULL) return false;
	matr.val = (int(*)[3])tmpP;
	for (int i = 0; i < val.size; i++){
		matr.val[i][0] = val.val[i][0];
		matr.val[i][1] = val.val[i][1];
		matr.val[i][2] = val.val[i][2];
	}
	return true;
}

bool subtractSparseMatrix(sparseMatrix  minuend, sparseMatrix subtract, sparseMatrix &result){ //减法
	if (minuend.cols != subtract.cols || minuend.rows != subtract.rows) return false;
	if (result.val != NULL) free(result.val);
	void *tmpP = malloc(sizeof(int) * 3 * (minuend.size + subtract.size));
	if (tmpP == NULL) return false;
	result.val = (int(*)[3])tmpP;
	result.cols = minuend.cols;
	result.rows = minuend.rows;
	result.size = 0;
	int minX, minY, subX, subY, i, j;
	i = j = 0;
	while (i < minuend.size && j < subtract.size){
		minX = minuend.val[i][1];
		minY = minuend.val[i][2];
		subX = subtract.val[j][1];
		subY = subtract.val[j][2];
		if (minY*minuend.cols + minX < subY*subtract.cols + subX){
			result.val[result.size][0] = minuend.val[i][0];
			result.val[result.size][1] = minuend.val[i][1];
			result.val[result.size][2] = minuend.val[i][2];
			i++;
		}else if (minY*minuend.cols + minX == subY*subtract.cols + subX){
			if (minuend.val[i][0] - subtract.val[j][0] == 0){
				result.size--;
			}else{
				result.val[result.size][0] = minuend.val[i][0] - subtract.val[j][0];
				result.val[result.size][1] = minuend.val[i][1];
				result.val[result.size][2] = minuend.val[i][2];
			}
			i++; j++;
		}else{
			result.val[result.size][0] = 0 - subtract.val[j][0];
			result.val[result.size][1] = subtract.val[j][1];
			result.val[result.size][2] = subtract.val[j][2];
			j++;
		}
		result.size++;
	}
	while (i < minuend.size){
		result.val[result.size][0] = minuend.val[i][0];
		result.val[result.size][1] = minuend.val[i][1];
		result.val[result.size][2] = minuend.val[i][2];
		i++; result.size++;
	}
	while (j < subtract.size){
		result.val[result.size][0] = 0 - subtract.val[j][0];
		result.val[result.size][1] = subtract.val[j][1];
		result.val[result.size][2] = subtract.val[j][2];
		j++; result.size++;
	}
	//重新分配内存，进一步减少内存开销
	return true;
}

bool plusSparseMatrix(sparseMatrix plused, sparseMatrix plus, sparseMatrix &result){ //加法
	if (plused.cols != plus.cols || plused.rows != plus.rows) return false;
	if (result.val != NULL) free(result.val);
	void *tmpP = malloc(sizeof(int) * 3 * (plused.size + plus.size));
	if (tmpP == NULL) return false;
	result.val = (int(*)[3])tmpP;
	result.cols = plused.cols;
	result.rows = plused.rows;
	result.size = 0;
	int minX, minY, subX, subY, i, j;
	i = j = 0;
	while (i < plused.size && j < plus.size){
		minX = plused.val[i][1];
		minY = plused.val[i][2];
		subX = plus.val[j][1];
		subY = plus.val[j][2];
		if (minY*plused.cols + minX < subY*plus.cols + subX){
			result.val[result.size][0] = plused.val[i][0];
			result.val[result.size][1] = plused.val[i][1];
			result.val[result.size][2] = plused.val[i][2];
			i++;
		}
		else if (minY*plused.cols + minX == subY*plus.cols + subX){
			if (plused.val[i][0] + plus.val[j][0] == 0){
				result.size--;
			}else{
				result.val[result.size][0] = plused.val[i][0] + plus.val[j][0];
				result.val[result.size][1] = plused.val[i][1];
				result.val[result.size][2] = plused.val[i][2];
			}
			i++; j++;
		}else{
			result.val[result.size][0] = plus.val[j][0];
			result.val[result.size][1] = plus.val[j][1];
			result.val[result.size][2] = plus.val[j][2];
			j++;
		}
		result.size++;
	}
	while (i < plused.size){
		result.val[result.size][0] = plused.val[i][0];
		result.val[result.size][1] = plused.val[i][1];
		result.val[result.size][2] = plused.val[i][2];
		i++; result.size++;
	}
	while (j < plus.size){
		result.val[result.size][0] = plus.val[j][0];
		result.val[result.size][1] = plus.val[j][1];
		result.val[result.size][2] = plus.val[j][2];
		j++; result.size++;
	}
	//重新分配内存，进一步减少内存开销
	return true;
}

bool multiplicationSparseMatrix(sparseMatrix multipled, sparseMatrix multiple, sparseMatrix &result){ //乘法
	if (multipled.cols != multiple.rows) return false;
	if (result.val != NULL) free(result.val);
	void *tmpP = malloc(sizeof(int) * 3 * (multipled.size + multiple.size));
	if (tmpP == NULL) return false;
	result.val = (int(*)[3])tmpP;
	result.rows = multipled.rows;
	result.cols = multiple.cols;
	result.size = 0;

	for (int k = 0; k < multipled.rows; k++){
		for (int m = 0; m < multiple.cols; m++){
			result.val[result.size][0] = 0;
			for (int i = 0; i < multipled.size; i++){			
				if (k != multipled.val[i][2]) continue;
				for (int j = 0; j < multiple.size; j++){
					if ( m != multiple.val[j][1]) continue;
					if (multipled.val[i][1] != multiple.val[j][2]) continue;
					result.val[result.size][0] += multipled.val[i][0] * multiple.val[j][0];
				}
			}
			if (result.val[result.size][0] != 0){
				result.val[result.size][1] = m;
				result.val[result.size][2] = k;
				result.size++;
			}
		}
	}
	return true;
}

bool transposeSparseMatrix(sparseMatrix val, sparseMatrix &result){ //转置
	if (val.size <= 0 || val.val == NULL) return false;
	if (result.val != NULL) free(result.val);
	void * tmpP = malloc(sizeof(int) * 3 * val.size);
	if (tmpP == NULL) return false;
	result.val = (int(*)[3])tmpP;
	result.cols = val.rows;
	result.rows = val.cols;
	result.size = val.size;

	int index = 0;
	int* pRes = trasition(val);
	for (int i = 0; i < val.size; i++){
		index = pRes[val.val[i][1]]++;
		result.val[index][0] = val.val[i][0];
		result.val[index][1] = val.val[i][2];
		result.val[index][2] = val.val[i][1];
	}
	return true;
}

int * trasition(sparseMatrix &val){
	void * tmpP1 = malloc(sizeof(int)*val.cols);
	void * tmpP2 = malloc(sizeof(int)*val.cols);
	if (tmpP1 == NULL || tmpP2 == NULL) return false;
	int* tmpArr1 = (int*)tmpP1;
	int* pRes = (int*)tmpP2;
	int k = 0;
	while (k < val.cols){
		tmpArr1[k] = pRes[k] = 0;
		k++;
	}

	for (int i = 0; i < val.size; i++){
		tmpArr1[val.val[i][1]]++;
	}

	pRes[0] = 0;
	for (int i = 0; i <val.cols-1; i++){
		pRes[i+1] = pRes[i] + tmpArr1[i];
	}
	free(tmpArr1);
	return pRes;
}

bool showSparseMatrix(sparseMatrix matr){
	if (matr.val == NULL){
		cout << "矩阵已被销毁，打印失败" << endl;
		return false;
	}
	if (matr.cols*matr.rows == 0){
		cout << "矩阵为空,打印失败" << endl;
		return false;
	}
	int current, index;
	index = current = 0;
	for (int i = 0; i < matr.size; i++){
		current = matr.val[i][2] * matr.cols + matr.val[i][1];
		while (index < current){
			cout << 0 << "(" << index%matr.cols << "," << index/matr.cols << ")" << "\t";
			if (++index%matr.cols == 0) cout << endl;
		}
		cout << matr.val[i][0] << "(" << index%matr.cols << "," << index/matr.cols << ")" << "\t";
		if (++index%matr.cols == 0) cout << endl;
	}

	int total = matr.cols*matr.rows;
	while (index < total){
		cout << 0 << "(" << index%matr.cols << "," << index / matr.cols << ")" << "\t";
		if (++index%matr.cols == 0) cout << endl;
	}
	cout << "\n\n";
	return true;
}









