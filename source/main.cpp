#include "make_text.h"
#include "print_text.h"
#include "sort.h"

int main()
{
    ERRORS error = NO_ERR;

    const char* filename = "Onegin.txt";

    text onegin = FillText(filename, &error);
    if (error != NO_ERR) {
        fprintf(stderr, "main.cpp/FillText(): %d\n", __LINE__ - 2);
    }

    if (PrintText("originaltext.txt", onegin) == OPEN_FILE_ERR)
    {
        fprintf(stderr, "main.cpp: %d\n", __LINE__ - 2);
    }

    SortBubbleArray(&onegin, StrcmpRightLeft);

    if (PrintText("BubbleSort.txt", onegin) == OPEN_FILE_ERR)
    {
        fprintf(stderr, "main.cpp: %d\n", __LINE__ - 2);
    }

    SortByQsort(&onegin);

    if (PrintText("qsort.txt", onegin) == OPEN_FILE_ERR)
    {
        fprintf(stderr, "main.cpp: %d\n", __LINE__ - 2);
    }

    FreeText(&onegin);

    return 0;
}
