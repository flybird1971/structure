/*
* �����㷨����������ð�����򣬿������򣬶����򣬹鲢���򣬻�������
*
* author flybird1971@gmail.com
* since  2015-05-27
*/

#pragma once

#include <stdio.h>
#include <iostream>

void insertSort(int* data,int length); //��������
void insertSortX(int* data, int length);
int binSearchLt(int* data, int begin, int end, int val);
int binSearch(int* data, int begin, int end, int val);
void insertSortEx(int* data, int length);
void bubbleSort(int* data, int length); //ð������


int deuce(int* data, int begin, int end);
bool quickSort(int* data, int begin, int end);  //��������


void heapSort(int* data,  int length);   // ������


void unic(int* data, int begin, int med, int end);
bool mergeSort(int* data, int begin, int end);  //�鲢����


bool count(int* data, int lenght, int digit, int* offsetArr);
void radixSort(int* data, int length);  //��������
