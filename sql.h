#pragma once

#include <stdio.h>
#include <iostream>
using namespace std;


//定义静态列表的大小
const int   STATIC_QUEUE_SIZE = 100 ;


// TODO: reference additional headers your program requires here
//定义静态有序线性列表
 typedef struct static_list{

	 //静态数组，用于存储数据
	 int (*pArr)[];

	 //静态队列大小
	 int size;

	 //静态队列存储元素个数
	 int length;
}SQLIST;

 /***************** 声明静态队列的12种常用方法 ***************************/
 //初始化静态队列
 void initList(SQLIST &list);

 //销毁静态队列
 void destoryList(SQLIST &list);

 //清空静态队列
 void clearList(SQLIST &list);

 //判断静态队列是否为空
 bool emptyList(SQLIST list);
 
 //插入元素
 int insertElement(SQLIST &list,int pos, int newEle);
 
 //删除元素
 int deleteElement(SQLIST &list, int postion, int &oldEle);
 
 //获取指定位置元素
 int getElement(SQLIST list,int postion, int &ele);
 
 //查找元素
 int locateEle(SQLIST list, int ele);
 
 //队列长度
 int getLenght(SQLIST list);

 //获取前驱
 int getProvion(SQLIST list, int element, int &provion);
 
 //获取后继
 int getNext(SQLIST list, int element, int &next);

 //遍历队列
 void traversalList(SQLIST &list);