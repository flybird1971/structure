/*
* 栈 测试
*
* author flybird1971@gmail.com
* since  2015-05-15
*/
#pragma once

#include"stdafx.h"
#include "error_code.h"
#include <iostream>
#include "stack_test.h"

using namespace std;
/*
//栈应用一：十进制转二进制
int dectobin(){
	cout << "enter  unsigned int value  : " << endl;
	int num;
	cin >> num;
	while (num >= 0){
		stack st;
		initStack(st);
		do{
			pushStack(st, num % 2);
			num = num / 2;
		} while (num > 0);
		travservalStack(st);
		destoryStack(st);
		cout << endl << "---------------------------------------" << endl;
		cin >> num;
	}
	return 0;
}

//栈应用二：汉诺塔
void initHannuo(){
	//初始化
	cout << "enter unsinged int (gt 0) " << endl;
	int level;
	cin >> level;
	while (level > 0){
		stack from, buffer, to;
		initStack(from); initStack(buffer); initStack(to);
		for (int i = level; i > 0; i--){
			pushStack(from, i);
		}
		cout << endl << "from data " << endl;
		travservalStack(from);
		cout << "-----" << endl;
		hannuota(level, from, buffer, to);
		travservalStack(to);
		destoryStack(from); destoryStack(buffer); destoryStack(to);
		cout << "---------------------------------------" << endl;
		cin >> level;
	}
}

int hannuota(int level, stack &from, stack &buffer, stack &to){
	if (level <= 0) return 0;
	//处理
	int tmpVal;
	if (level == 1){
		popStack(from, tmpVal);
		pushStack(to, tmpVal);
	}
	else{
		hannuota(level - 1, from, to, buffer);
		popStack(from, tmpVal);
		pushStack(to, tmpVal);
		hannuota(level - 1, buffer, from, to);
	}
	return 0;
}

//调试 栈
bool debugStack(){
	stack st;
	initStack(st);
	cout << "stack length is " << getStackLength(st) << endl;
	travservalStack(st);

	for (int i = 0; i < 200; i++){
		if (pushStack(st, i) == false) return false;
	}
	//travservalStack(st);

	stackType tmp;
	for (int i = 0; i < 100; i++){
		if (popStack(st, tmp) == false) return false;
		cout << "pop stack value is " << tmp << endl;
	}
	//clearStack(st);
	//destoryStack(st);
	cout << "stack length is " << getStackLength(st) << endl;
	travservalStack(st);
	return 0;
}
//*/