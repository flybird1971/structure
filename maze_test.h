/*
* 迷宫求解
*
* author flybird1971@gmail.com
* since  2015-05-15
*/
#pragma once
#include <stdio.h>
#include "error_code.h"
#include "stack.h"
//*

typedef int(direction)[4]; //定义方向数据类型

void unpackDirect(int val, direction &director); //求解迷宫

int packDirect(direction dir);

bool initDirection(int(*data)[5][5], stackType &current, int xLenght, int yLenght);

bool jumpNext(direction &dir, int i, stackType &current, stackType &nextPos, stack &sA);

int maze();
//*/