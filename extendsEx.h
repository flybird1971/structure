/* 
 * �������ģ����ú������ڴ˴�
 * 
 * author flybird1971@gmail.com
 * since  2015-05-25
 */

#pragma once

#include <stdio.h>

const int CHAR_TYPE = 1;
const int INT_TYPE  = 2;

void printArr(int* arr, int size, int lineNum); //��ӡ����
void* createArrByType(int type, int size);//�����ڴ棬ģ������