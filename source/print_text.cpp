#include "print_text.h"

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
