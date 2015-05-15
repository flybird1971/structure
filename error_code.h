#pragma once
//用于定义各种错误代码

//静态队列，查询不存在
const int  STATIC_QUEUE_ELEMENT_NO_EXIST  =  -1;

//双向链表插入位置溢出
const int DOUBLY_LIST_OVERFLOW			  =  -1;

//双向链表，查找元素不存在
const int DOUBLY_LIST_NOT_EXISTS		  =  -1;

//队列为空
const int  STATIC_QUEUE_IS_EMPTY          =   0;

//双向链表，前驱不存在
const int DOUBLY_LIST_NOT_PREVIOUS		  =   0;

//双向链表，后驱不存在
const int DOUBLY_LIST_NOT_NEXT			  =   0;

//内存分配失败
const int ALLOCA_ERROR					  =   0;

//处理正确
const int  OK                             =   100;

//查询静态数组，索引不合法，溢出
const int  STATIC_QUEUE_OVERFLOW		  =   101;

//队列第一个元素
const int  STATIC_QUEUE_ELEMENT_IS_FIRST  =   102;

//队列中最后一个元素
const int  STATIC_QUEUE_ELEMENT_IS_LAST   =   103;


