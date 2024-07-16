#include "cseries/cseries.h"

#include <stdlib.h>

/* ---------- code */

void qsort_2byte(
    void *base,
    size_t num,
    compare_function_2byte compare)
{
    qsort(base, num, 2, (int(*)(const void *, const void *))compare);
}

void qsort_4byte(
    void *base,
    size_t num,
    compare_function_4byte compare)
{
    qsort(base, num, 4, (int(*)(const void *, const void *))compare);
}
