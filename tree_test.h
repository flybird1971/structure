/*
* 树 测试
*
* author flybird1971@gmail.com
* since  2015-05-20
*/
#pragma once
#include <stdio.h>
#include "error_code.h"
#include "tree.h"
#include "bTree.h"
#include "stack.h"

void debugTree();   //普通树调试
void debugBTree();  //二叉树调试

void findLeafPath();   //查找并打印每个叶子的路径
//void haffmanTree();  //哈弗曼树
//void haffmanEcode(); //哈弗曼加密，编码