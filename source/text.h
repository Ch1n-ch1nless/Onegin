#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <TXLib.h>

struct line
{
    char* str_ptr;
    size_t str_len;
};

struct text
{
    FILE* file_ptr;
    size_t buf_size;
    char* buffer;
    size_t line_size;
    line* line_array;

};

#endif // TEXT_H_INCLUDED
