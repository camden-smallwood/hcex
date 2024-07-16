#include "cseries/cseries.h"
#include "memory/array.h"

#include <stdlib.h>
#include <string.h>

/* ---------- public code */

void dynamic_array_new(
    dynamic_array *array,
    size_t element_size)
{
    assert(array);
    assert(element_size > 0);

    array->element_size = element_size;
    array->count = 0;
    array->elements = NULL;
}

bool dynamic_array_resize(
    dynamic_array *array,
    size_t count)
{
    assert(array);
    assert(array->element_size > 0);
    assert((array->count != 0) == (array->elements != NULL));

    if (count == array->count)
        return true;

    uint8_t *elements = (uint8_t *)realloc(array->elements, array->element_size * count);

    if ((count != 0) != (elements != NULL))
        return false;

    size_t index = array->count;

    if (count > index)
        memset(&elements[array->element_size * index], 0, (count - index) * array->element_size);

    array->count = count;
    array->elements = elements;

    return true;
}

void dynamic_array_delete(
    dynamic_array *array)
{
    assert(array);
    assert(array->element_size > 0);
    assert((array->count != 0) == (array->elements != NULL));
    
    array->element_size = NONE;
    array->count = NONE;

    if (array->elements)
    {
        free(array->elements);
        array->elements = NULL;
    }
}

int dynamic_array_add_element(
    dynamic_array *array)
{
    assert(array);
    assert(array->element_size > 0);
    assert((array->count != 0) == (array->elements != NULL));

    size_t index = array->count;

    if (index >= INT_MAX)
        return NONE;

    size_t new_count = index + 1;
    uint8_t *elements = (uint8_t *)realloc(array->elements, array->element_size * new_count);

    if (!elements)
        return NONE;

    memset(&elements[array->element_size * index], 0, array->element_size);

    array->count = new_count;
    array->elements = elements;

    return (int)index;
}

void *dynamic_array_get_element(
    const dynamic_array *array,
    int index,
    size_t element_size)
{
    assert(array);
    assert(array->element_size > 0);
    assert(array->element_size == element_size);
    assert(array->count > 0);
    assert((array->count != 0) == (array->elements != NULL));
    assert(index >= 0 && index < array->count);

    return (uint8_t *)array->elements + (array->element_size * index);
}

void dynamic_array_delete_element(
    dynamic_array *array,
    int index)
{
    assert(array);
    assert(array->element_size > 0);
    assert(array->count > 0);
    assert((array->count != 0) == (array->elements != NULL));
    assert(index >= 0 && index < array->count);

    size_t new_count = array->count - 1;
    array->count = new_count;

    if ((size_t)index < new_count)
    {
        size_t element_size = array->element_size;
        uint8_t *element = (uint8_t *)array->elements + array->element_size * index;

        memmove(element, element + element_size, (new_count - index) * element_size);
    }

    array->elements = realloc(array->elements, array->element_size * array->count);
}

void static_array_new(
    size_t *count,
    void *elements,
    size_t element_size,
    size_t maximum_count)
{
    assert(count);
    assert(elements);
    assert(element_size > 0);
    assert(maximum_count <= INT_MAX);

    *count = 0;
    memset(elements, NONE, element_size * maximum_count);
}

bool static_array_resize(
    size_t *count,
    void *elements,
    size_t element_size,
    size_t maximum_count,
    size_t new_count)
{
    assert(count);
    assert(*count >= 0);
    assert(elements);
    assert(element_size > 0);
    assert(maximum_count <= INT_MAX);

    if (new_count >= maximum_count)
        return false;

    size_t current_count = *count;

    if (current_count == new_count)
        return true;

    uint8_t *old_elements_end = (uint8_t *)elements + (element_size * current_count);
    uint8_t *new_elements_end = (uint8_t *)elements + (element_size * new_count);

    size_t memset_size;
    int memset_value;

    if (new_elements_end <= old_elements_end)
    {
        memset_size = old_elements_end - new_elements_end;
        memset_value = NONE;
    }
    else
    {
        memset_size = new_elements_end - old_elements_end;
        memset_value = 0;
        new_elements_end = old_elements_end;
    }

    memset(new_elements_end, memset_value, memset_size);
    *count = new_count;

    return true;
}

int static_array_add_element(
    size_t *count,
    void *elements,
    size_t element_size,
    size_t maximum_count)
{
    assert(count);
    assert(*count >= 0);
    assert(elements);
    assert(element_size > 0);
    assert(maximum_count <= INT_MAX);

    size_t index = *count;

    if (index >= maximum_count)
        return NONE;
    
    *count = index + 1;

    memset((uint8_t *)elements + (index * element_size), 0, element_size);

    return (int)index;
}

void *static_array_get_element(
    size_t count,
    const void *elements,
    size_t element_size,
    int index)
{
    assert(count > 0);
    assert(elements);
    assert(element_size > 0);
    assert(index >= 0 && index < count);

    return (uint8_t *)elements + element_size * index;
}

void static_array_delete_element(
    size_t *count,
    const void *elements,
    size_t element_size,
    int index)
{
    assert(count);
    assert(*count >= 0);
    assert(elements);
    assert(element_size > 0);
    assert(index >= 0 && index < *count);

    size_t new_count = --(*count);

    if ((size_t)index < new_count)
        memmove(
            (uint8_t *)elements + (element_size * index),
            (uint8_t *)elements + ((element_size * index) + element_size),
            (new_count - (size_t)index) * element_size);
    
    memset(
        (uint8_t *)elements + (new_count * element_size),
        NONE,
        element_size);
}
