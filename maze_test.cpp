/*
 * �Թ����
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
//ջӦ�������Թ���� ��Ҫ�޸�stack.h�ļ�
int maze(){
	//��ʼ��
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
			//��������ͬ,��ԭ�ϸ�����������forѭ��
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

//�����¸��ڵ�
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

//��ʼ����ǰλ�ã�����
bool initDirection(int(*data)[5][5], stackType &current, int xLenght, int yLenght){
	direction dir = {};
	unpackDirect(current[2], dir);
	if (current[1] - 1 < 0 || (*data)[current[1] - 1][current[0]] == 0)  dir[0] = 0;		     //�Ϸ�λ�Ƿ��ͨ  y���� -1
	if (current[0] + 1 >= xLenght || (*data)[current[1]][current[0] + 1] == 0) dir[1] = 0;    //�ҷ�λ�Ƿ��ͨ  x���� +1
	if (current[1] + 1 >= yLenght || (*data)[current[1] + 1][current[0]] == 0)  dir[2] = 0;    //�·�λ�Ƿ��ͨ  y���� +1
	if (current[0] - 1 < 0 || (*data)[current[1]][current[0] - 1] == 0) dir[3] = 0;            //��λ�Ƿ��ͨ  x���� -1
	current[2] = packDirect(dir);
	return true;
}

//˳ʱ�� 0=>��  1=>��  2=>��  3=>�� 
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