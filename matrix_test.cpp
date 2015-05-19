/*
* �����ʾ��������������
*
* author flybird1971@gmail.com
* since  2015-05-18
*/
#pragma once

#include"stdafx.h"
#include "error_code.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "matrix_test.h"

using namespace std;

//���� ����
/*
 * ����ĸ�ֵ����Ҫrows��cols��ͬ,����ʧ��
 * ����ļӼ����� ��ѽrows,cols��ͬ������ʧ��
 * ����ĳ˷����� ��ҪAxB BxC�����ľ��󣬷���ʧ��
 */
void debugMatrix(){

	//����ֵ����
	matrix matrTest1, matrTest2,matrTest3;
	initMatrix(matrTest1, 4, 3);
	initMatrix(matrTest2, 3, 5);
	initMatrix(matrTest3, 3, 5);
	int val1[12] = { 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0 };
	int val2[15] = { 0, 2, 6, 2, 1, 0, 3, 1, 0, 0, 1, 0, 0, 23, 12 };
	int val3[15] = { 1, 2, 3, 1, 0, 0, 3, -1, -2, 0, 23, 4, 0, 0, 0 };
	assignMatrix(matrTest1, val1, 12);
	assignMatrix(matrTest2, val2, 15);
	//assignMatrix(matrTest3, matrTest2);
	assignMatrix(matrTest3, val3,15);
	showMatrix(matrTest1);
	showMatrix(matrTest2);

	//����Ӽ�����
	matrix matrixRes;
	initMatrix(matrixRes, matrTest2.rows, matrTest2.cols);
	if (subtractMatrix(matrTest2, matrTest3, matrixRes) == false) cout << "ʧ��" << endl;
	//showMatrix(matrixRes);
	if (plusMatrix(matrTest2, matrTest3, matrixRes) == false) cout << "ʧ��" << endl;
	//showMatrix(matrixRes);

	//����˷�����
	matrix muMatrixRes;
	initMatrix(muMatrixRes, matrTest1.rows, matrTest2.cols);
	if (multiplicationMatrix(matrTest1, matrTest2, muMatrixRes) == false) cout << "ʧ��" << endl;
	cout <<"---------------------------------\nrows " << muMatrixRes.rows << " cols " << muMatrixRes.cols << endl;
	//showMatrix(muMatrixRes);

	//����ת�ò���
	matrix tranMatrixRes;
	initMatrix(tranMatrixRes, matrTest1.cols, matrTest1.rows);
	if (transposeMatrix(matrTest1, tranMatrixRes) == false) cout << "ʧ��" << endl;
	cout << "---------------------------------\nrows " << tranMatrixRes.rows << " cols " << tranMatrixRes.cols << endl;
	showMatrix(tranMatrixRes);

	destoryMatrix(tranMatrixRes);
	showMatrix(tranMatrixRes);
}

/*
* ϡ�����ĸ�ֵ����Ҫrows��cols��ͬ,����ʧ��
* ϡ�����ļӼ����� ��ѽrows,cols��ͬ������ʧ��
* ϡ�����ĳ˷����� ��ҪAxB BxC�����ľ��󣬷���ʧ��
*/
void debugSparseMatrix(){

	//ϡ�����ֵ����
	sparseMatrix matrTest1, matrTest2, matrTest3;
	initSparseMatrix(matrTest1);
	initSparseMatrix(matrTest2);
	initSparseMatrix(matrTest3);
	int val1[3][3] = { { 1, 3, 0 }, { -1, 0, 2 }, { 2, 1, 3 },};  //4x6
	int val2[6][3] = { { 5, 4, 0 }, { 2, 1, 1 }, { -1, 4, 1 },   //6x5
					   { 3, 3, 2 }, { 1, 1, 4 }, { -1, 3, 5 }, 
					 };
	int val3[3][3] = { { 1, 4, 0 }, { 1, 0, 2 }, { -1, 0, 3 },}; //4x6
	assignSparseMatrix(matrTest1, val1, 3, 4, 6);
	assignSparseMatrix(matrTest2, val2, 6, 6, 5);
	assignSparseMatrix(matrTest3, val3, 3, 4, 6);
	//showSparseMatrix(matrTest1);
	//showSparseMatrix(matrTest2);
	//showSparseMatrix(matrTest3);
	//assignSparseMatrix(matrTest3, matrTest2);
	//cout << "------------------------------" << endl;
	//showSparseMatrix(matrTest2);
	//showSparseMatrix(matrTest3);
	
	//ϡ�����Ӽ�����
	//plusSparseMatrix(matrTest1, matrTest3, matrTest2);
	//cout << "--------------after sub operate -----------" << endl;
	//showSparseMatrix(matrTest1);
	//showSparseMatrix(matrTest3);
	//showSparseMatrix(matrTest2);

	//ϡ�����˷�����
	int val4[4][3] = { { 1, 2, 0 }, { 1, 1, 1 }, { 1, 2, 1 }, { 1, 2, 2 }, }; //3x3
	int val5[3][3] = { { 2, 0, 1 }, { 1, 1, 1 }, { 2, 1, 2 }, }; //3x3
	sparseMatrix matrTest11, matrTest12;
	initSparseMatrix(matrTest11);
	initSparseMatrix(matrTest12);
	assignSparseMatrix(matrTest11, val4, 4, 3, 3);
	assignSparseMatrix(matrTest12, val5, 3, 3, 3);
	multiplicationSparseMatrix(matrTest11, matrTest12, matrTest3);
	//showSparseMatrix(matrTest11);
	//showSparseMatrix(matrTest12);
	//showSparseMatrix(matrTest3);

	//ϡ�����ת��
	transposeSparseMatrix(matrTest2, matrTest3);
	showSparseMatrix(matrTest2);
	//showSparseMatrix(matrTest3);
	
	//����
	destorySparseMatrix(matrTest2);
	showSparseMatrix(matrTest2);
}