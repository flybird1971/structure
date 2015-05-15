/*
* �Թ����
*
* author flybird1971@gmail.com
* since  2015-05-15
*/
#pragma once
#include <stdio.h>
#include "error_code.h"
#include "stack.h"
//*

typedef int(direction)[4]; //���巽����������

void unpackDirect(int val, direction &director); //����Թ�

int packDirect(direction dir);

bool initDirection(int(*data)[5][5], stackType &current, int xLenght, int yLenght);

bool jumpNext(direction &dir, int i, stackType &current, stackType &nextPos, stack &sA);

int maze();
//*/