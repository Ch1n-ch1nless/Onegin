#include "onegin.h"
#include "sort.h"

int main()
{
    const char* filename = "Onegin.txt";

    text onegin = FillText(filename);

    PrintNotSortedArray(&onegin);

    PrintSortedByEndArray(&onegin);

    PrintSortedByBeginArray(&onegin);

    FreeText(&onegin);

    return 0;
}
