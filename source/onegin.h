#ifndef ONEGIN_H_INCLUDED
#define ONEGIN_H_INCLUDED

#include "text.h"
#include "sort.h"

#define REDASSERT(str) "\033[0;31m" #str "\033[0m"

text FillText(const char* filename);
void OpenFile(text* onegin, const char* filename);
void ReadBuffer(text* onegin);
size_t FillLineArray(text* onegin);

void PrintText(FILE* file_ptr, text onegin);
void PrintSortedByEndArray(text* onegin);
void PrintSortedByBeginArray(text* onegin);
void PrintNotSortedArray(text* onegin);

void FreeText(text* onegin);

#endif // ONEGIN_H_INCLUDED
