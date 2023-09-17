#include "onegin.h"

text FillText(const char* filename, ERRORS* error)
{
    text onegin = {.file_ptr   = nullptr,
                   .buf_size   = 0,
                   .buffer     = nullptr,
                   .line_size  = 0,
                   .line_array = nullptr};

    if (OpenFile(&onegin, filename) == OPEN_FILE_ERR) {
        *error = OPEN_FILE_ERR;
        return onegin;
    }

    if (ReadBuffer(&onegin) == MEM_ALLOC_ERR) {
        *error = MEM_ALLOC_ERR;
        return onegin;
    }

    size_t count_of_lines = FillLineArray(&onegin, error);

    if (count_of_lines <= onegin.line_size) {
        onegin.line_size = count_of_lines;
    } else {
        printf("ERROR! count_of_lines: %d \n line_size!: %d\n", count_of_lines, onegin.line_size);
        assert(0);
    }

    return onegin;
}

ERRORS OpenFile(text* onegin, const char* filename)
{
    struct stat st = {};

    onegin->file_ptr = fopen(filename, "r");
    if (onegin->file_ptr == nullptr) {
        printf("onegin.cpp/OpenFile() : %d\n\tError! Program can NOT open file: %s.txt!\n", __LINE__ - 2,
                                                                                            filename);
        return OPEN_FILE_ERR;
    }

    stat(filename, &st);
    onegin->buf_size = st.st_size;
    return NO_ERR;
}

ERRORS ReadBuffer(text* onegin)
{
    assert(onegin);
    assert(onegin->file_ptr);

    onegin->buffer = (char*) calloc(onegin->buf_size + 1, sizeof(char));
    if (onegin->buffer == nullptr) {
        printf("onegin.cpp/ReadBuffer(): %d\n\tError! Program can NOT allocate memory!", __LINE__ -2);
        return MEM_ALLOC_ERR;
    }

    const size_t symbol_number = fread(onegin->buffer, sizeof(char), onegin->buf_size, onegin->file_ptr);
    if (symbol_number != onegin->buf_size) {
        #if 0
        if (feof(onegin->file_ptr)) {
            printf("Error reading %s: unexpected end of file\n", filename);
        } else if (ferror(onegin->file_ptr)) {
            printf("Error reading %s", filename);
        }
        #endif
        if (symbol_number < onegin->buf_size) {
            char* buffer = onegin->buffer + symbol_number;

            for (size_t i = 0; i < onegin->buf_size; i++) {
                 *buffer = '\0';
                 buffer++;
            }
        } else {
            printf("ERROR! Symbols in Onegin.txt  more then buf_size!");
            assert(0);
        }
    }

    fclose(onegin->file_ptr);
    onegin->file_ptr = nullptr;
    return NO_ERR;
}

size_t FillLineArray(text* onegin, ERRORS* error)
{
    assert(onegin);
    assert(onegin->buffer);

    onegin->line_size = onegin->buf_size / 2 + 1;
    onegin->line_array = (line*) calloc(onegin->line_size, sizeof(line));
    if (onegin->line_array == nullptr) {
        *error = MEM_ALLOC_ERR;
        fprintf(stderr, "onegin.cpp/FillLineArray(): %d\n", __LINE__ - 3);
        return 0;
    }

    size_t count_of_lines = 0;

    line* temp_array = onegin->line_array;
    temp_array->str_ptr = onegin->buffer;

    for (size_t i = 1; i < onegin->buf_size; i++) {
        if (*(onegin->buffer + i) == '\n')
        {
            *(onegin->buffer + i) = '\0';
            i++;
            *(onegin->buffer + i) = '\0';

            size_t length = (onegin->buffer + i) - temp_array->str_ptr - 1;
            temp_array->str_len = length;

            i++;
            temp_array++;
            temp_array->str_ptr =  (onegin->buffer + i);

            count_of_lines++;

        }
        else if (*(onegin->buffer) == '\0')
        {
            size_t length = (onegin->buffer + i) - temp_array->str_ptr;
            temp_array->str_len = length;

            count_of_lines++;

            return count_of_lines;
        }
    }
    return count_of_lines;
}

ERRORS PrintText(char* filename, text onegin)
{
    assert(onegin.line_array);

    FILE* file_ptr = fopen(filename, "w");
    if (file_ptr == nullptr) {
        fprintf(stderr, "onegin.cpp/PrintText() : %d\n\tError! Program can NOT open file: %s\n", __LINE__ - 2,
                                                                                                 filename);
        return OPEN_FILE_ERR;
    }

    for (size_t i = 0; i < onegin.line_size; i++) {
        if ((onegin.line_array)->str_ptr) {
            fprintf(file_ptr, "[%d] %s\n", i, (onegin.line_array)->str_ptr);
            (onegin.line_array)++;
        } else {
            fprintf(file_ptr, "END OF FILE!!!");
            break;
        }
    }

    if (file_ptr != nullptr) {
        fclose(file_ptr);
    }
    return NO_ERR;
}

void FreeText(text* onegin)
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
