#include "onegin.h"
#include "sort.h"

int main()
{
    const char* filename = "Onegin.txt";

    text onegin = FillText(filename);

    PrintText("originaltext.txt", onegin);

    SortBubbleArray(&onegin, StrcmpRightLeft);

    PrintText("BUbbleSort.txt", onegin);

    SortByQsort(&onegin);

    PrintText("qsort.txt",onegin);

    FreeText(&onegin);

    return 0;
}
