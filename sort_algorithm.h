/*
* ÅÅĞòËã·¨£¨²åÈëÅÅĞò£¬Ã°ÅİÅÅĞò£¬¿ìËÙÅÅĞò£¬¶ÑÅÅĞò£¬¹é²¢ÅÅĞò£¬»ùÊıÅÅĞò£©
*
* author flybird1971@gmail.com
* since  2015-05-27
*/

#pragma once

#include <stdio.h>
#include <iostream>

void insertSort(int* data,int length); //²åÈëÅÅĞò
void insertSortX(int* data, int length);
int binSearchLt(int* data, int begin, int end, int val);
int binSearch(int* data, int begin, int end, int val);
void insertSortEx(int* data, int length);
void bubbleSort(int* data, int length); //Ã°ÅİÅÅĞò


int deuce(int* data, int begin, int end);
bool quickSort(int* data, int begin, int end);  //¿ìËÙÅÅĞò


void heapSort(int* data,  int length);   // ¶ÑÅÅĞò


void unic(int* data, int begin, int med, int end);
bool mergeSort(int* data, int begin, int end);  //¹é²¢ÅÅĞò


bool count(int* data, int lenght, int digit, int* offsetArr);
void radixSort(int* data, int length);  //»ùÊıÅÅĞò
