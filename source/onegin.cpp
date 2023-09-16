#include "onegin.h"

text FillStructText(const char* filename)
{
    text onegin = {.file_ptr   = nullptr,
                   .buf_size   = 0,
                   .buffer     = nullptr,
                   .line_size  = 0,
                   .line_array = nullptr};

    if(OpenFile(&onegin, filename) != NOERROR) {
        ...
    }

    ReadBuffer(&onegin);

    size_t count_of_lines = FillLineArray(&onegin);

    if (count_of_lines <= onegin.line_size) {
        onegin.line_size = count_of_lines;
    } else {
        printf("ERROR! count_of_lines: %d \n line_size!: %d", count_of_lines, onegin.line_size);
    }

    return onegin;
}

void OpenFile(text* onegin, const char* filename)
{
    assert(text ? filename);
    struct stat st = {};

    onegin->file_ptr = fopen(filename, "r");
    if (onegin->file_ptr == nullptr) {
        // assert(REDASSERT("Error! Program can NOT find the file"));
        FAILED_OPEN_FILE;
        return;
    }

    stat(filename, &st);
    onegin->buf_size = st.st_size;
}

void ReadBuffer(text* onegin)
{
    assert(onegin);

    onegin->buffer = (char*) calloc(onegin->buf_size + 1, sizeof(char));
    if (onegin->buffer == nullptr) {
        printf("Error with memory! Program can NOT find free memory. BUY NEW HD, SSD and RAM!!!");
        return;
    }

    const size_t symbol_number = fread(onegin->buffer, sizeof(char), onegin->buf_size, onegin->file_ptr);
    if (symbol_number != onegin->buf_size) {
        #if 0
        if (feof(onegin->file_ptr)) {
            printf("Error reading %s: unexpected end of file\n", filename);
        } else if (ferror(onegin->file_ptr)) {
            printf("Error reading %s", filename);
        }

        ClearStructTextBuffer(onegin);
        #endif
        if (symbol_number < onegin->buf_size) {
            char* buffer = onegin->buffer + symbol_number;

            for (size_t i = 0; i < onegin->buf_size; i++) {
                 *buffer = '\0';
                 buffer++;
            }
        } else {
            printf("ERROR! Symbols in Onegin.txt  more then buf_size!");
            return;
        }
    }

    fclose(onegin->file_ptr);
    onegin->file_ptr = nullptr;
}

size_t FillLineArray(text* onegin)
{
    assert(onegin);
    assert(onegin->buffer);

    onegin->line_size = onegin->buf_size / 2 + 1;
    onegin->line_array = (line*) calloc(onegin->line_size, sizeof(line));

    size_t count_of_lines = 0;

    line* temp_array = onegin->line_array;
    temp_array->str_ptr = onegin->buffer;

    for (size_t i = 1; i < onegin->buf_size; i++) {
        onegin->buffer++;
        if (*(onegin->buffer) == '\n')
        {
            //printf("Нашли \\n на позиции: %d\n", i);
            *(onegin->buffer) = '\0';
            ++(onegin->buffer);
            i++;
            //printf("Нашли \\n на позиции: %d\n", i);
            *(onegin->buffer) = '\0';

            size_t length = onegin->buffer - temp_array->str_ptr - 1;
            temp_array->str_len = length;
            //printf("Длина строки № %d : %d\n\n", count_of_lines, length);

            ++(onegin->buffer);
            temp_array++;
            temp_array->str_ptr =  onegin->buffer;

            count_of_lines++;

        }
        else if (*(onegin->buffer) == '\0')
        {
            //printf("Нашли конец файла на позиции: %d\n", i);

            size_t length = onegin->buffer - temp_array->str_ptr;
            temp_array->str_len = length;

            //printf("Длина строки № %d : %d\n\n", count_of_lines, length);

            count_of_lines++;

            return count_of_lines;
        }
    }
    return 0;
}

void PrintStructText(FILE* file_ptr, text onegin)
{
    assert(onegin.line_array);

    for (size_t i = 0; i < onegin.line_size; i++) {
        if ((onegin.line_array)->str_ptr) {
            fprintf(file_ptr, "[%d] %s\n", i, (onegin.line_array)->str_ptr);
            (onegin.line_array)++;
        } else {
            fprintf(file_ptr, "END OF FILE!!!");
            break;
        }
    }
}

void FreeStructText(text* onegin)
{
    free(onegin->buffer);
    onegin->buffer = nullptr;
    onegin->buf_size = 0;

    free(onegin->line_array);
    onegin->line_array = nullptr;
    onegin->line_size = 0;

    if (onegin->file_ptr != nullptr) {
        fclose(onegin->file_ptr);
        onegin->file_ptr = nullptr;
    }
}

void PrintSortedByBeginArray(text* onegin)
{
    assert(onegin);

    FILE* file_ptr = fopen("qsort.txt", "w");
    if (file_ptr == nullptr) {
        printf("Error! Program can NOT open file: qsort.txt!\n");
        return;
    }

    fprintf(file_ptr, "Left->Right:\n\n");
    SortByQsort(onegin);
    PrintStructText(file_ptr, *onegin);

    fclose(file_ptr);
}

void PrintSortedByEndArray(text* onegin)
{
    assert(onegin);

    FILE* file_ptr = fopen("BubbleSort.txt", "w");
    if (file_ptr == nullptr) {
        printf("Error! Program can NOT open file: BubbleSort.txt!\n");
        return;
    }

    fprintf(file_ptr, "Right->Left:\n\n");
    SortBubbleArray(onegin, StrcmpRightLeft);
    PrintStructText(file_ptr, *onegin);

    fclose(file_ptr);
}

void PrintNotSortedArray(text* onegin)
{
    assert(onegin);

    FILE* file_ptr = fopen("originaltext.txt", "w");
    if (file_ptr == nullptr) {
        printf("Error! Program can NOT open file: originaltext.txt!\n");
        return;
    }

    fprintf(file_ptr, "Original:\n\n");
    PrintStructText(file_ptr, *onegin);

    fclose(file_ptr);
}

