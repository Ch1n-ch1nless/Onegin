#include "onegin.h"
#include "sort.h"

int main()
{
    const char* filename = "Onegin.txt";

    text onegin = FillStructText(filename);

    PrintNotSortedArray(&onegin);

    PrintSortedByEndArray(&onegin);

    PrintSortedByBeginArray(&onegin);

    FreeStructText(&onegin);

    return 0;
}
