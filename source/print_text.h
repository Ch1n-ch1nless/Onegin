#ifndef PRINT_TEXT_H_INCLUDED
#define PRINT_TEXT_H_INCLUDED

#include "text.h"

#define REDASSERT(str) "\033[0;31m" #str "\033[0m"

ERRORS PrintText(char* filename, text onegin);

void FreeText(text* onegin);

#endif // PRINT_TEXT_H_INCLUDED
