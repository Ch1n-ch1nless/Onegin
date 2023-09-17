#ifndef ONEGIN_H_INCLUDED
#define ONEGIN_H_INCLUDED

#include "text.h"

#define REDASSERT(str) "\033[0;31m" #str "\033[0m"

text FillText(const char* filename, ERRORS* error);
ERRORS OpenFile(text* onegin, const char* filename);
ERRORS ReadBuffer(text* onegin);
size_t FillLineArray(text* onegin, ERRORS* error);

#endif // ONEGIN_H_INCLUDED
