/*
 * 迷宫求解
 *
 * author flybird1971@gmail.com
 * since  2015-05-15
 */
#pragma once

#include"stdafx.h"
#include "error_code.h"
#include <iostream>
#include "maze_test.h"

using namespace std;
//*
//栈应用三：迷宫求解 需要修改stack.h文件
int maze(){
	//初始化
	stack sA;
	initStack(sA);
	int xLenght = 5;
	int yLenght = 5;
	int data[5][5] = {
		{ 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 1, 1 },
		{ 1, 0, 0, 0, 1 },
		{ 0, 1, 1, 0, 1 },
	};

	stackType current = { 0, 0, 15 };
	stackType nextPos = {};
	stackType outCoord = { 4, 4, 15 };
	direction dir = {};
	while (current[0] != outCoord[0] || current[1] != outCoord[1]){
		unpackDirect(current[2], dir);
		initDirection((int(*)[5][5])data, current, xLenght, yLenght);
		unpackDirect(current[2], dir);
		for (int i = 0; i < 4; i++){
			//进入死胡同,还原上个场景，跳出for循环
			if (dir[i] == 0 && i == 3){
				popStack(sA, current);
				break;
			}
			if (dir[i] == 0) continue;
			jumpNext(dir, i, current, nextPos, sA);
			break;
		}
	}
	pushStack(sA, outCoord);
	travservalStack(sA);
	return 0;
}

//跳到下个节点
bool jumpNext(direction &dir, int i, stackType &current, stackType &nextPos, stack &sA){
	dir[i] = 0;
	current[2] = packDirect(dir);
	switch (i){
	case 0:
		nextPos[0] = current[0];
		nextPos[1] = current[1] - 1;
		nextPos[2] = 11;
		break;
	case 1:
		nextPos[0] = current[0] + 1;
		nextPos[1] = current[1];
		nextPos[2] = 7;
		break;
	case 2:
		nextPos[0] = current[0];
		nextPos[1] = current[1] + 1;
		nextPos[2] = 14;
		break;
	case 3:
		nextPos[0] = current[0] - 1;
		nextPos[1] = current[1];
		nextPos[2] = 13;
		break;
	default: break;
	}
	pushStack(sA, current);
	current[0] = nextPos[0];
	current[1] = nextPos[1];
	current[2] = nextPos[2];
	//cout << "jump after .... current direction is " << current[2] << endl;
	return true;
}

//初始化当前位置，方向
bool initDirection(int(*data)[5][5], stackType &current, int xLenght, int yLenght){
	direction dir = {};
	unpackDirect(current[2], dir);
	if (current[1] - 1 < 0 || (*data)[current[1] - 1][current[0]] == 0)  dir[0] = 0;		     //上方位是否可通  y坐标 -1
	if (current[0] + 1 >= xLenght || (*data)[current[1]][current[0] + 1] == 0) dir[1] = 0;    //右方位是否可通  x坐标 +1
	if (current[1] + 1 >= yLenght || (*data)[current[1] + 1][current[0]] == 0)  dir[2] = 0;    //下方位是否可通  y坐标 +1
	if (current[0] - 1 < 0 || (*data)[current[1]][current[0] - 1] == 0) dir[3] = 0;            //左方位是否可通  x坐标 -1
	current[2] = packDirect(dir);
	return true;
}

//顺时针 0=>上  1=>右  2=>下  3=>左 
int packDirect(direction dir){
	int val = dir[0] | dir[1] | dir[2] | dir[3];
	return val;
}

void unpackDirect(int val, direction &director){
	director[0] = val & 1;
	director[1] = val & 2;
	director[2] = val & 4;
	director[3] = val & 8;
}
// */