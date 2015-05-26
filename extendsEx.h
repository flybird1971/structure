/* 
 * 帮助中心，常用函数放于此处
 * 
 * author flybird1971@gmail.com
 * since  2015-05-25
 */

#pragma once

#include <stdio.h>

const int CHAR_TYPE = 1;
const int INT_TYPE  = 2;

void printArr(int* arr, int size, int lineNum); //打印数组
void* createArrByType(int type, int size);//开辟内存，模拟数组