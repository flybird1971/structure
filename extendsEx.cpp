/*
* �������ģ����ú������ڴ˴�
*
* author flybird1971@gmail.com
* since  2015-05-25
*/
#pragma once

#include"stdafx.h"
#include <stdio.h>
#include <iostream>
#include "extendsEx.h"

using namespace std;

//��ӡ����
void printArr(int* arr, int size, int lineNum){
	if (size < 1 || arr == NULL) return;
	for (int i = 0; i < size; i++){
		cout << arr[i] << "\t";
		if (lineNum>1 && (i + 1) % lineNum == 0) cout << endl;
	}
}
