#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
    PElement *arr;
    DEL_FUNC delete_func;
    COPY_FUNC copy_func;
    PRINT_FUNC print_func;
    int array_size;
} AdptArray, *PAdptArray; // the definetion here is usless tho because evgeni did it in the header file

PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df, PRINT_FUNC pf)
{
    PAdptArray array = (PAdptArray)malloc(sizeof(AdptArray));
    if (array == NULL)
    {
        return NULL;
    }
    array->arr = calloc(1, sizeof(PElement));
    if (array->arr == NULL)
    {
        return NULL;
    }
    array->delete_func = df;
    array->copy_func = cf;
    array->print_func = pf;
    array->array_size = 0;
    return array;
}

void DeleteAdptArray(PAdptArray array)
{
    if (array == NULL)
    {
        return; // the array hasnt been created yet
    }
    int i;
    for (i = 0; i < array->array_size; i++)
    {
        if (array->arr[i] != NULL)
        {
            array->delete_func(array->arr[i]);
        }
    }
    free(array->arr);
    free(array);
}

Result SetAdptArrayAt(PAdptArray array, int idx, PElement element)
{
    if (idx == 0) // it is useless to allocate new memory.
    {
        if ((GetAdptArrayAt(array, idx) != NULL))
        {
            array->delete_func(array->arr[idx]);
        }
        array->arr[idx] = array->copy_func(element);
        array->array_size = idx + 1;
        return SUCCESS;
    }

    if (array->array_size <= idx)
    {
        PElement *tmp = calloc(idx + 1, sizeof(PElement));
        if (tmp == NULL)
        {
            printf("failed to set the element\n");
            return FAIL;
        }
        memcpy(tmp, array->arr, array->array_size * sizeof(PElement));
        free(array->arr);
        array->arr = tmp;
        array->array_size = idx + 1;
    }
    if ((GetAdptArrayAt(array, idx) != NULL))
    {
        array->delete_func(array->arr[idx]);
    }

    array->arr[idx] = array->copy_func(element);

    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray array, int idx)
{
    if (idx < 0)
    {
        printf("index cannot be negative\n");
        return NULL;
    }
    if (array->array_size <= idx)
    {
        printf("this element not in the array\n");
        return NULL;
    }
    if (array->arr[idx] == NULL)
    {
        return NULL;
    }
    PElement tmp = array->copy_func(array->arr[idx]);
    return tmp;
}

int GetAdptArraySize(PAdptArray array)
{
    return array->array_size;
}

void PrintDB(PAdptArray array)
{
    int i;
    for (i = 0; i < array->array_size; i++)
    {
        if (array->arr[i] != NULL)
        {
            array->print_func(array->arr[i]);
        }
    }
}
