/*
 * �����ʾ��������������
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

//ϡ�����
typedef struct SPARSE_MATRIX{
	int (*val)[3];
	unsigned size,rows,cols;
}sparseMatrix, *pSparseMatrix;

bool initMatrix(matrix &matr,unsigned rows,unsigned cols);

bool destoryMatrix(matrix &matr);

bool assignMatrix(matrix &matr, eleMatrixType val[], int length);

bool assignMatrix(matrix &matr, matrix val);

bool subtractMatrix(matrix  minuend, matrix subtract, matrix &result); //����

bool plusMatrix(matrix plused, matrix plus, matrix &result); //�ӷ�

bool multiplicationMatrix(matrix multipled, matrix multiple, matrix &result); //�˷�

bool transposeMatrix(matrix val, matrix &result); //ת��

void showMatrix(matrix matr);

// ---------------------------- ϡ����� ���� ---------------------------------
bool initSparseMatrix(sparseMatrix &matr, unsigned rows, unsigned cols);

bool destorySparseMatrix(sparseMatrix &matr);

bool assignSparseMatrix(sparseMatrix &matr, eleMatrixType val[],int length);

bool assignSparseMatrix(sparseMatrix &matr, sparseMatrix val);

bool subtractSparseMatrix(sparseMatrix  minuend, sparseMatrix subtract, sparseMatrix &result); //����

bool plusSparseMatrix(sparseMatrix plused, sparseMatrix plus, sparseMatrix &result); //�ӷ�

bool multiplicationSparseMatrix(sparseMatrix multipled, sparseMatrix multiple, sparseMatrix &result); //�˷�

bool transposeSparseMatrix(sparseMatrix val, sparseMatrix &result); //ת��

void showSparseMatrix(sparseMatrix matr);

int * trasition(sparseMatrix &val);
//*/








