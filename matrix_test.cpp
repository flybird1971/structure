/*
* 矩阵表示及常见矩阵运算
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

//矩阵 调试
/*
 * 矩阵的赋值，需要rows，cols相同,否则失败
 * 矩阵的加减操作 需呀rows,cols相同，否则失败
 * 矩阵的乘法操作 需要AxB BxC这样的矩阵，否则失败
 */
void debugMatrix(){

	//矩阵赋值测试
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

	//矩阵加减测试
	matrix matrixRes;
	initMatrix(matrixRes, matrTest2.rows, matrTest2.cols);
	if (subtractMatrix(matrTest2, matrTest3, matrixRes) == false) cout << "失败" << endl;
	//showMatrix(matrixRes);
	if (plusMatrix(matrTest2, matrTest3, matrixRes) == false) cout << "失败" << endl;
	//showMatrix(matrixRes);

	//矩阵乘法测试
	matrix muMatrixRes;
	initMatrix(muMatrixRes, matrTest1.rows, matrTest2.cols);
	if (multiplicationMatrix(matrTest1, matrTest2, muMatrixRes) == false) cout << "失败" << endl;
	cout <<"---------------------------------\nrows " << muMatrixRes.rows << " cols " << muMatrixRes.cols << endl;
	//showMatrix(muMatrixRes);

	//矩阵转置测试
	matrix tranMatrixRes;
	initMatrix(tranMatrixRes, matrTest1.cols, matrTest1.rows);
	if (transposeMatrix(matrTest1, tranMatrixRes) == false) cout << "失败" << endl;
	cout << "---------------------------------\nrows " << tranMatrixRes.rows << " cols " << tranMatrixRes.cols << endl;
	showMatrix(tranMatrixRes);

	destoryMatrix(tranMatrixRes);
	showMatrix(tranMatrixRes);
}

/*
* 稀疏矩阵的赋值，需要rows，cols相同,否则失败
* 稀疏矩阵的加减操作 需呀rows,cols相同，否则失败
* 稀疏矩阵的乘法操作 需要AxB BxC这样的矩阵，否则失败
*/
void debugSparseMatrix(){

	//稀疏矩阵赋值测试
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
	
	//稀疏矩阵加减测试
	//plusSparseMatrix(matrTest1, matrTest3, matrTest2);
	//cout << "--------------after sub operate -----------" << endl;
	//showSparseMatrix(matrTest1);
	//showSparseMatrix(matrTest3);
	//showSparseMatrix(matrTest2);

	//稀疏矩阵乘法测试
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

	//稀疏矩阵转置
	transposeSparseMatrix(matrTest2, matrTest3);
	showSparseMatrix(matrTest2);
	//showSparseMatrix(matrTest3);
	
	//销毁
	destorySparseMatrix(matrTest2);
	showSparseMatrix(matrTest2);
}