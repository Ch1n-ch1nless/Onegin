#include "sort.h"

void SortBubbleArray(text* onegin, int (*comp)(const line, const line))
{
    assert(onegin);
    assert(onegin->line_array);

    for (size_t i = 0; i < onegin->line_size; i++) {
        for (size_t j = i+1; j < onegin->line_size; j++) {

            if ((onegin->line_array + j) == nullptr) break;

            int is_str1_smaller_str2 = (*comp)(*(onegin->line_array + i), *(onegin->line_array + j));

            if (is_str1_smaller_str2 > 0)
            {
                line temp_pt = *(onegin->line_array + i);
                *(onegin->line_array + i) = *(onegin->line_array + j);
                *(onegin->line_array + j) = temp_pt;
            }
        }
        if ((onegin->line_array + i) == nullptr) break;
    }
}

void SortByQsort(text* onegin)
{
    qsort((void *)onegin->line_array, onegin->line_size, sizeof(line), Compare);
}

int Compare(const void * str1, const void * str2)
{
    return StrcmpLeftRight( * ( line* ) str1, * ( line* ) str2 );
}

int StrcmpRightLeft(const line line1, const line line2)
{
    char* str1 = line1.str_ptr;
    char* str2 = line2.str_ptr;

    size_t str1_len = line1.str_len;
    size_t str2_len = line2.str_len;

    size_t i = str1_len-1;
    size_t j = str2_len-1;

    while (true)
    {
        while (i > 0) {
            assert(str1 + i);

            if ('a' <= str1[i] && str1[i] <= 'z') break;
            if ('A' <= str1[i] && str1[i] <= 'Z') break;
            //printf("Пропускаем элемент в строке str1: %c\n", str1[i]);
            i--;
        }
        //printf("Сравниваем последний буквенный элемент в строке str1: %c\n", str1[i]);

        while (j > 0) {
            assert(str2 + j);

            if ('a' <= str2[j] && str2[j] <= 'z') break;
            if ('A' <= str2[j] && str2[j] <= 'Z') break;
            //printf("Пропускаем элемент в строке str2: %c\n", str2[j]);
            j--;
        }
        //printf("Сравниваем последний буквенный элемент в строке str2: %c\n", str2[j]);

        if (str1[i] > str2[j]) {
            return 1;
        } else if (str1[i] < str2[j]) {
            return -1;
        } else {
            i--;
            j--;
        }

        if (i >= str1_len || j >= str2_len) break;
    }

    if (i < str1_len && j < str2_len) {
        return str1[i] <= str2[j];
    } else if (i >= str1_len) {
        return -1;
    } else {
        return 1;
    }
}

int StrcmpLeftRight(const line line1, const line line2)
{
    char* str1 = line1.str_ptr;
    char* str2 = line2.str_ptr;

    size_t str1_len = line1.str_len;
    size_t str2_len = line2.str_len;

    size_t i = 0;
    size_t j = 0;

    while (true)
    {
        while (i < str1_len) {
            if ('a' <= str1[i] && str1[i] <= 'z') break;
            if ('A' <= str1[i] && str1[i] <= 'Z') break;
            //printf("Пропускаем элемент в строке str1: %c\n", str1[i]);
            i++;
        }
        //printf("Сравниваем последний буквенный элемент в строке str1: %c\n", str1[i]);

        while (j < str2_len) {
            if ('a' <= str2[j] && str2[j] <= 'z') break;
            if ('A' <= str2[j] && str2[j] <= 'Z') break;
            //printf("Пропускаем элемент в строке str2: %c\n", str2[j]);
            j++;
        }
        //printf("Сравниваем последний буквенный элемент в строке str2: %c\n", str2[j]);

        if (str1[i] > str2[j]) {
            return 1;
        } else if (str1[i] < str2[j]) {
            return -1;
        } else {
            i++;
            j++;
        }

        if (i >= str1_len || j >= str2_len) break;
    }

    if (i < str1_len && j < str2_len) {
        return str1[i] <= str2[j];
    } else if (i >= str1_len) {
        return -1;
    } else {
        return 1;
    }
}

