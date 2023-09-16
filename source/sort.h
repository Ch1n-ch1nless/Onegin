#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include "text.h"

void SortBubbleArray(text* onegin, int (*comp)(const line, const line));
void SortByQsort(text* onegin);

int Compare(const void * str1, const void * str2);
int StrcmpRightLeft(const line str1, const line str2);
int StrcmpLeftRight(const line str1, const line str2);

void MyQuickSort(text* onegin, int (*comp)(const line, const line));
size_t MyPartition(text* onegin, int (*comp)(const line, const line));

#endif // SORT_H_INCLUDED
