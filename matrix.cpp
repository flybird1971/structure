/*
* 矩阵表示及常见矩阵运算
*
* author flybird1971@gmail.com
* since  2015-05-17
*/

#pragma once

#include"stdafx.h"
/*
#include "error_code.h"
#include <iostream>
#include "matrix.h"

using namespace std;

//初始化
bool initMatrix(matrix &matr, unsigned rows, unsigned cols){
	void *tmpP = malloc(sizeof(eleMatrixType)*rows*cols);
	if (tmpP == NULL) return false;
	matr.val  = (eleMatrixType*)tmpP;
	matr.cols = cols;
	matr.rows = rows;
	return true;
}

bool destoryMatrix(matrix &matr){
	if (matr.val == NULL) return false;
	free(matr.val);
	matr.val  = NULL;
	matr.cols = 0;
	matr.rows = 0;
	return true;
}

bool assignMatrix(matrix &matr, eleMatrixType val[],int length){
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
	result.rows = minuend.rows;
	result.cols = minuend.cols;
	for (int i = 0; i < minuend.rows; i++){
		for (int j = 0; j < minuend.cols; j++){
			result.val[i + j] = minuend.val[i + j] - subtract.val[i + j];
		}
	}
	return true;
}

bool plusMatrix(matrix plused, matrix plus, matrix &result){ //加法
	if (plused.rows != plus.rows || plused.cols != plus.cols) return false;
	result.rows = plused.rows;
	result.cols = plused.cols;
	for (int i = 0; i < plused.rows; i++){
		for (int j = 0; j < plused.cols; j++){
			result.val[i + j] = plused.val[i + j] + plus.val[i + j];
		}
	}
	return true;
}

bool multiplicationMatrix(matrix multipled, matrix multiple, matrix &result){ //乘法
	if (multipled.cols != multiple.rows) return false;
	result.rows = multipled.cols;
	result.cols = multiple.rows;
	for (int i = 0; i < multipled.rows; i++){
		for (int j = 0; j < multiple.cols; j++){
			result.val[i + j] = 0;
			for (int k = 0; k < multiple.rows; k++){
				result.val[i + j] += multipled.val[i*multipled.cols + k] * multiple.val[j*multiple.cols + k];
			}
		}
	}
	return true;
}

bool transposeMatrix(matrix val, matrix &result){ //转置
	result.rows = val.cols;
	result.cols = val.rows;
	int length = val.rows*val.cols;
	int rows, cols,newIndex;
	for (int i = 0; i < length; i++){
		rows = i/val.cols;
		cols = i%val.cols;
		newIndex = cols*result.cols + rows;
		result.val[newIndex] = val.val[i];
	}
	return true;
}

void showMatrix(matrix matr){
	int length = matr.cols*matr.rows;
	if (length == 0) return false;
	for (int i = 0; i < length; i++){
		cout << matr.val[i] << "\t";
		if ((i + 1) % matr.cols == 0) cout << endl;
	}
}

// ---------------------------- 稀疏矩阵 操作 ---------------------------------
bool initSparseMatrix(sparseMatrix &matr, unsigned rows, unsigned cols){
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

bool assignSparseMatrix(sparseMatrix &matr, int(*val)[3], int length,int rows,int cols){
	if (matr.val != NULL) free(matr.val);
	void * tmpP = malloc(sizeof(int) * 3 * length);
	if (tmpP == NULL) return false;
	matr.val = (int(*)[3] )tmpP;
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
	matr.size = val.size;
	matr.cols = val.cols;
	matr.rows = val.rows;
	if (matr.val != NULL) free(matr.val);
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
	void *tmpP = malloc(sizeof(int)*3 * (minuend.size + subtract.size) );
	if (tmpP == NULL) return false;
	result.val  = (int(*)[3])tmpP;
	result.cols = minuend.cols;
	result.rows = minuend.rows;
	result.size = 0;
	int minRows, minCols, subRows, subCols,i,j;
	i = j = 0;
	while (i < minuend.size && j < subtract.size){
		minRows = minuend.val[i][1];
		minCols = minuend.val[i][2];
		subRows = subtract.val[i][1];
		subCols = subtract.val[i][2];
		if (minRows*minuend.cols + minCols < subRows*subtract.cols + subCols){
			result.val[result.size][0] = minuend.val[i][0];
			result.val[result.size][1] = minuend.val[i][1];
			result.val[result.size][2] = minuend.val[i][2];
			i++; 
		}else if (minRows*minuend.cols + minCols == subRows*subtract.cols + subCols){
			result.val[result.size][0] = minuend.val[i][0] - subtract.val[j][0] ;
			if (result.val[result.size][0] == 0) result.size--;
			result.val[result.size][1] = minuend.val[i][1];
			result.val[result.size][2] = minuend.val[i][2];
			i++; j++;
		}else{
			result.val[result.size][0] = 0 - subtract.val[j][0];
			result.val[result.size][1] = subtract.val[i][1];
			result.val[result.size][2] = subtract.val[i][2];
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
		result.val[result.size][1] = subtract.val[i][1];
		result.val[result.size][2] = subtract.val[i][2];
		j++; result.size++;
	}
	//重新分配内存，进一步减少内存开销
	return true;
}

bool plusSparseMatrix(sparseMatrix plused, sparseMatrix plus, sparseMatrix &result){ //加法
	if (plused.cols != plus.cols || plused.rows != plus.rows) return false;
	void *tmpP = malloc(sizeof(int) * 3 * (plused.size + plused.size));
	if (tmpP == NULL) return false;
	result.val = (int(*)[3])tmpP;
	result.cols = plused.cols;
	result.rows = plused.rows;
	result.size = 0;
	int minRows, minCols, subRows, subCols, i, j;
	i = j = 0;
	while (i < plused.size && j < plus.size){
		minRows = plused.val[i][1];
		minCols = plused.val[i][2];
		subRows = plus.val[i][1];
		subCols = plus.val[i][2];
		if (minRows*plused.cols + minCols < subRows*plus.cols + subCols){
			result.val[result.size][0] = plused.val[i][0];
			result.val[result.size][1] = plused.val[i][1];
			result.val[result.size][2] = plused.val[i][2];
			i++;
		}
		else if (minRows*plused.cols + minCols == subRows*plus.cols + subCols){
			result.val[result.size][0] = plused.val[i][0] + plus.val[j][0];
			if (result.val[result.size][0] == 0) result.size--;
			result.val[result.size][1] = plused.val[i][1];
			result.val[result.size][2] = plused.val[i][2];
			i++; j++;
		}
		else{
			result.val[result.size][0] = plus.val[j][0];
			result.val[result.size][1] = plus.val[i][1];
			result.val[result.size][2] = plus.val[i][2];
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
		result.val[result.size][1] = plus.val[i][1];
		result.val[result.size][2] = plus.val[i][2];
		j++; result.size++;
	}
	//重新分配内存，进一步减少内存开销
	return true;
}

bool multiplicationSparseMatrix(sparseMatrix multipled, sparseMatrix multiple, sparseMatrix &result){ //乘法
	if (multipled.cols != multiple.rows) return false;
	result.rows = multipled.cols;
	result.cols = multiple.rows;
	int index = 0;
	for (int i = 0; i < multipled.size; i++){
		for (int j = 0; j < multiple.size; j++){
			result.val[i + j] = 0;
			for (int k = 0; k < multiple.rows; k++){
				if (multipled.val[i][2] != multiple.val[i][1]) continue;
				result.val[index] += multipled.val[i*multipled.cols + k] * multiple.val[j*multiple.cols + k];
				result.val[index][1] = multipled.val[i][2];
				result.val[index][2] = multiple.val[i][1];
			}
			index++;
		}
	}
	return true;
}

bool transposeSparseMatrix(sparseMatrix val, sparseMatrix &result){ //转置
	if (val.size <= 0 || val.val == NULL) return false;
	if (result.val != NULL) free(result.val);
	void * tmpP = malloc(sizeof(int) * 3 * val.size);
	if (tmpP == NULL) return false;
	result.val  = (int(*)[3])tmpP;
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
	int  num, index;
	num = index = 0;
	for (int i = 0; i < val.size; i++){
		if (val.val[i][1] == index){
			num++;
		}else{
			i--;
			index++;
			num = 0;
		}
		tmpArr1[index] = num;
	}

	num = 0; pRes[0] = 0;
	for (int i = 0; i <index; i++){
		pRes[i + 1] = pRes[i] + tmpArr1[i];
	}
	free(tmpP1);
	return pRes;
}

void showSparseMatrix(sparseMatrix matr){
	if (matr.cols*matr.rows == 0) return false;
	int current,count,index;
	count = index = current = 0;
	for (int i = 0; i < matr.size; i++){
		current = matr.val[i][2]*matr.rows + matr.val[i][1];
		while(index < current){
			cout << 0 <<"(" <<index/matr.rows <<"," <<index%matr.rows <<")" <<"\t";
			if (++count%matr.cols == 0) cout << endl;
		}
		index = current + 1;
		cout << matr.val[i][0] << "(" << index / matr.rows << "," << index%matr.rows << ")" << "\t";
		if (++count%matr.cols == 0) cout << endl;
	}
}
//*/









