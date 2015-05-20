/*
 * 矩阵表示及常见矩阵运算
 * 
 * author flybird1971@gmail.com
 * since  2015-05-17
 */

#pragma once
/*
#include <stdio.h>
#include <iostream>

typedef    int  eleMatrixType;

typedef struct MATRIX_TYPE{
	eleMatrixType * val;
	unsigned rows;
	unsigned cols;
}matrix,*pMatrix;

//稀疏矩阵
typedef struct SPARSE_MATRIX{
	int (*val)[3];
	unsigned size,rows,cols;
}sparseMatrix, *pSparseMatrix;

bool initMatrix(matrix &matr,unsigned rows,unsigned cols);

bool destoryMatrix(matrix &matr);

bool assignMatrix(matrix &matr, eleMatrixType val[], int length);

bool assignMatrix(matrix &matr, matrix val);

bool subtractMatrix(matrix  minuend, matrix subtract, matrix &result); //减法

bool plusMatrix(matrix plused, matrix plus, matrix &result); //加法

bool multiplicationMatrix(matrix multipled, matrix multiple, matrix &result); //乘法

bool transposeMatrix(matrix val, matrix &result); //转置

void showMatrix(matrix matr);

// ---------------------------- 稀疏矩阵 操作 ---------------------------------
bool initSparseMatrix(sparseMatrix &matr, unsigned rows, unsigned cols);

bool destorySparseMatrix(sparseMatrix &matr);

bool assignSparseMatrix(sparseMatrix &matr, eleMatrixType val[],int length);

bool assignSparseMatrix(sparseMatrix &matr, sparseMatrix val);

bool subtractSparseMatrix(sparseMatrix  minuend, sparseMatrix subtract, sparseMatrix &result); //减法

bool plusSparseMatrix(sparseMatrix plused, sparseMatrix plus, sparseMatrix &result); //加法

bool multiplicationSparseMatrix(sparseMatrix multipled, sparseMatrix multiple, sparseMatrix &result); //乘法

bool transposeSparseMatrix(sparseMatrix val, sparseMatrix &result); //转置

void showSparseMatrix(sparseMatrix matr);

int * trasition(sparseMatrix &val);
//*/








