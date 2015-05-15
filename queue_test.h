/*
* This file implements doubly linked list
* 队列 测试
*
* author flybird1971@gmail.com
* since  2015-05-15
*/
#pragma once
#include <stdio.h>
#include "error_code.h"
#include "queue.h"
#include "circle_queue.h"

void debugQueue();
void debugCircleQueue();
bool triangleDeal(); //杨辉三角,使用循环队列处理
