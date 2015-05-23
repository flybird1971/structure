/*
* This file implements stack by array
* 使用数组 实现栈
*
* author flybird1971@gmail.com
* since  2015-05-15
*/

#pragma once

#include"stdafx.h"
#include "error_code.h"
#include <iostream>
#include "stack.h"

using namespace std;

/* 6 basic operation  */
bool initStack(stack &st){
	st.top = 0;
	return true;
}

bool clearStack(stack &st){
	st.top = 0;
	return true;
}

bool destoryStack(stack &st){
	st.top = 0;
	return true;
}

bool pushStack(stack &st, stackType val){
	if (st.top + 1 == STACK_LENGTH) return false;
	st.values[st.top] = val;
	/**st.values[st.top][0] = val[0];
	st.values[st.top][1] = val[1];
	st.values[st.top][2] = val[2];//*/
	st.top++;
	return true;
}

bool popStack(stack &st, stackType &val){
	if (--st.top < 0) return false;
	val = st.values[st.top];
	/**val[0] = st.values[st.top][0];
	val[1] = st.values[st.top][1];
	val[2] = st.values[st.top][2];//*/
	return true;
}

int  getStackLength(stack st){
	return st.top;
}

void travservalStack(stack st){
	int tmpIndex = st.top-1;
	while (tmpIndex >= 0){
		cout << st.values[tmpIndex--] <<"\t"<< endl;
		//cout << st.values[tmpIndex--];  //十进制转二进制实验
		//cout << st.values[tmpIndex--]<<endl; //汉诺塔实验
		//cout << st.values[tmpIndex][0] << st.values[tmpIndex--][1]<< endl; //迷宫实验
	}
}
