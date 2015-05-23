/*
* This file implements stack by array
* 使用数组 实现栈
*
* author flybird1971@gmail.com
* since  2015-05-15
*/
#pragma once
#include <stdio.h>
#include "error_code.h"

const int STACK_LENGTH = 1000;
//typedef int(stackType)[3]; //求解迷宫，特殊需求
//typedef int stackType;
typedef char stackType;

//节点
typedef struct stack_node{
	stackType values[STACK_LENGTH];
	unsigned int top;
}stack, *pStack;

/* 6 basic operation  */
bool initStack(stack &st);

bool clearStack(stack &st);

bool destoryStack(stack &st);

bool pushStack(stack &st, stackType val);

bool popStack(stack &st, stackType &val);

int  getStackLength(stack st);

void travservalStack(stack st);
