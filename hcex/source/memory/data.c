#include "cseries/cseries.h"
#include "memory/data.h"

#include <stdlib.h>
#include <string.h>

/* ---------- private prototypes */

static void data_compact(struct data_array *data);
static void datum_initialize(struct data_array *data, struct datum_header *header);

/* ---------- public code */

void data_verify(
    struct data_array *data)
{
    assert(data);
    assert(data->data);
    assert(data->signature == DATA_ARRAY_SIGNATURE);

    int16_t maximum_count = data->maximum_count;
    assert(maximum_count >= 0);

    int16_t count = data->count;
    assert(count >= 0);
    assert(count <= maximum_count);

    int16_t first_free_absolute_index = data->first_free_absolute_index;
    assert(first_free_absolute_index >= 0);
    assert(first_free_absolute_index <= maximum_count);

    int16_t actual_count = data->actual_count;
    assert(actual_count >= 0);
    assert(actual_count <= count);
}

struct data_array *data_new(
    const char *name,
    int16_t maximum_count,
    int16_t size)
{
    size_t allocation_size = data_allocation_size(maximum_count, size);
    
    struct data_array *array = malloc(allocation_size);

    if (array)
        data_initialize(array, name, maximum_count, size);

    return array;
}

size_t data_allocation_size(
    int16_t maximum_count,
    int16_t size)
{
    return sizeof(struct data_array) + (maximum_count * size);
}

void data_initialize(
    struct data_array *data,
    const char *name,
    int16_t maximum_count,
    int16_t size)
{
    assert(maximum_count > 0);
    assert(size > 0);
    assert(name);
    assert(data);

    memset(data, 0, sizeof(struct data_array));

    strncpy(data->name, name, sizeof(data->name) - 1);
    data->maximum_count = maximum_count;
    data->size = size;
    data->data = data + 1;
    data->signature = DATA_ARRAY_SIGNATURE;
    data->valid = false;
}

void data_dispose(
    struct data_array *data)
{
    data_verify(data);
    memset(data, 0, sizeof(*data));
    free(data);
}

void data_make_valid(
    struct data_array *data)
{
    data_verify(data);
    data->valid = true;
    data_delete_all(data);
}

void data_make_invalid(
    struct data_array *data)
{
    data_verify(data);
    data->valid = false;
}

int32_t datum_new_at_index(
    struct data_array *data,
    int32_t index)
{
    data_verify(data);
    assert(data->valid);

    int16_t absolute_index = DATUM_INDEX_GET_ABSOLUTE_INDEX(index);
    int16_t identifier = DATUM_INDEX_GET_IDENTIFIER(index);

    if (absolute_index < 0 || absolute_index >= data->maximum_count || identifier == 0)
        return NONE;

    struct datum_header *datum = (struct datum_header *)((uint8_t *)data->data + (absolute_index * data->size));

    if (datum->identifier != 0)
        return NONE;

    data->actual_count++;

    if (absolute_index >= data->count)
        data->count = absolute_index + 1;

    datum_initialize(data, datum);
    datum->identifier = identifier;

    return DATUM_INDEX_NEW(identifier, absolute_index);
}

int32_t datum_new_at_plain_index_hack_for_player_data(
    struct data_array *data,
    int32_t index)
{
    data_verify(data);
    assert(data->valid);

    int16_t absolute_index = DATUM_INDEX_GET_ABSOLUTE_INDEX(index);

    if (absolute_index < 0 || absolute_index >= data->maximum_count)
        return NONE;

    struct datum_header *datum = (struct datum_header *)((uint8_t *)data->data + (absolute_index * data->size));

    if (datum->identifier != 0)
        return NONE;

    data->actual_count++;

    if (absolute_index >= data->count)
        data->count = absolute_index + 1;

    datum_initialize(data, datum);

    return DATUM_INDEX_NEW(datum->identifier, absolute_index);
}

int32_t datum_new(
    struct data_array *data)
{
    data_verify(data);
    assert(data->valid);

    int16_t absolute_index = data->first_free_absolute_index;
    int16_t maximum_count = data->maximum_count;

    if (absolute_index >= maximum_count)
        return NONE;

    int16_t size = data->size;

    struct datum_header *datum = (struct datum_header *)((uint8_t *)data->data + (size * absolute_index));

    while (datum->identifier)
    {
        ++absolute_index;
        datum = (struct datum_header *)((uint8_t *)datum + size);

        if (absolute_index >= maximum_count)
            return NONE;
    }

    memset(datum, 0, size);

    datum->identifier = data->next_identifier;

    if (++data->next_identifier)
        data->next_identifier = (int16_t)(INT16_MAX + 1);

    ++data->actual_count;

    data->first_free_absolute_index = absolute_index + 1;

    if (data->count <= absolute_index)
        data->count = absolute_index + 1;

    return DATUM_INDEX_NEW(datum->identifier, absolute_index);
}

void datum_delete(
    struct data_array *data,
    int32_t index)
{
    struct datum_header *result = datum_get(data, index);
    result->identifier = 0;

    int16_t absolute_index = DATUM_INDEX_GET_ABSOLUTE_INDEX(index);

    if (absolute_index < data->first_free_absolute_index)
        data->first_free_absolute_index = index;

    if (absolute_index + 1 == data->count)
    {
        do
        {
            result = (struct datum_header *)((uint8_t *)result - data->size);
            --data->count;
        } while (data->count > 0 && !result->identifier);
    }

    --data->actual_count;
}

void data_delete_all(
    struct data_array *data)
{
    data_verify(data);
    assert(data->valid);

    data->count = 0;
    data->actual_count = 0;
    data->first_free_absolute_index = 0;

    strncpy((char *)&data->next_identifier, data->name, 2);
    data->next_identifier |= DATUM_BASE_IDENTIFIER;

    int16_t maximum_count = data->maximum_count;
    int16_t size = data->size;

    for (int16_t i = 0; i < maximum_count; i++)
    {
        struct datum_header *datum = (struct datum_header *)((uint8_t *)data->data + (i * size));
        datum->identifier = 0;
    }
}

void data_iterator_new(
    struct data_iterator *iterator,
    struct data_array *data)
{
    data_verify(data);
    assert(data->valid);

    iterator->data = data;
    iterator->signature = (tag)(uintptr_t)data ^ DATA_ITERATOR_SIGNATURE;
    iterator->absolute_index = 0;
    iterator->index = NONE;
}

void *data_iterator_next(
    struct data_iterator *iterator)
{
    assert(iterator);

    struct data_array *data = iterator->data;

    data_verify(data);
    assert(data->valid);

    vassert(
        iterator->signature == ((tag)(uintptr_t)data->name ^ DATA_ITERATOR_SIGNATURE),
        "uninitialized iterator passed to iterator_next()");

    int16_t absolute_index = iterator->absolute_index;
    int16_t count = data->count;

    if (absolute_index >= count)
    {
        iterator->absolute_index = absolute_index;
        return NULL;
    }

    int16_t size = data->size;

    struct datum_header *datum = (struct datum_header *)((uint8_t *)data->data + (size * absolute_index));

    while (true)
    {
        int32_t index = DATUM_INDEX_NEW(datum->identifier, absolute_index++);

        if (datum->identifier)
        {
            iterator->index = index;
            iterator->absolute_index = absolute_index;
            return datum;
        }

        datum = (struct datum_header *)((uint8_t *)datum + size);

        if (absolute_index >= count)
        {
            iterator->absolute_index = absolute_index;
            return NULL;
        }
    }
}

int32_t data_next_index(
    struct data_array *data,
    int32_t index)
{
    data_verify(data);
    assert(data->valid);

    int32_t next_index = index + 1;

    if (next_index < 0)
        return NONE;

    int16_t count = data->count;

    if (next_index >= count)
        return NONE;

    int16_t size = data->size;

    struct datum_header *datum = (struct datum_header *)((uint8_t *)data->data + (size * next_index));

    while (datum->identifier == 0)
    {
        ++next_index;

        datum = (struct datum_header *)((uint8_t *)datum + size);

        if (next_index >= count)
            return NONE;
    }

    return DATUM_INDEX_NEW(datum->identifier, next_index);
}

int32_t data_prev_index(
    struct data_array *data,
    int32_t index)
{
    data_verify(data);
    assert(data->valid);

    int16_t count = data->count;

    int16_t prev_index = index == NONE ? count - 1 : index - 1;

    if (prev_index < 0 || prev_index >= count)
        return NONE;

    int16_t size = data->size;

    struct datum_header *datum = (struct datum_header *)((uint8_t *)data->data + (prev_index * size));

    while (datum->identifier == 0)
    {
        datum = (struct datum_header *)((char *)datum - size);

#warning TODO: check if this postfix decrement is correct, may be a bungie typo
        if (prev_index-- < 0)
            return NONE;
    }

    return DATUM_INDEX_NEW(datum->identifier, prev_index);
}

void *datum_try_and_get(
    struct data_array *data,
    int32_t index)
{
    if (index == NONE)
        return NULL;

    assert(data->valid);

    int16_t identifier = DATUM_INDEX_GET_IDENTIFIER(index);
    assert(identifier || !data->identifier_zero_invalid);

    int16_t absolute_index = DATUM_INDEX_GET_ABSOLUTE_INDEX(index);

    if (absolute_index < 0 || absolute_index >= data->maximum_count)
        return NULL;

    struct datum_header *datum = (struct datum_header *)((uint8_t *)data->data + (absolute_index * data->size));

    int16_t datum_identifier = datum->identifier;

    if (datum_identifier == 0 || (identifier != 0 && datum_identifier != identifier))
        return NULL;

    return datum;
}

void *datum_get(
    struct data_array *data,
    int32_t index)
{
    assert(data->valid);

    int16_t identifier = DATUM_INDEX_GET_IDENTIFIER(index);
    assert(identifier || !data->identifier_zero_invalid);

    int16_t absolute_index = DATUM_INDEX_GET_ABSOLUTE_INDEX(index);
    assert(absolute_index >= 0 && absolute_index < data->count);

    struct datum_header *datum = (struct datum_header *)((uint8_t *)data->data + (absolute_index * data->size));

    int16_t datum_identifier = datum->identifier;
    assert(datum_identifier);
    assert(identifier == datum->identifier);

    return datum;
}

/* ---------- private code */

static void data_compact(
    struct data_array *data)
{
    data_verify(data);
    assert(data->valid);

    int16_t new_count = 0;
    void *new_data = malloc(data->maximum_count * data->size);

    if (!new_data)
        return;

    struct datum_header *datum = (struct datum_header *)data->data;

    for (int16_t i = 0; i < data->count; ++i)
    {
        if (datum->identifier)
            memcpy((uint8_t *)new_data + data->size * new_count++, datum, data->size);

        datum = (struct datum_header *)((uint8_t *)datum + data->size);
    }

    memcpy(data->data, new_data, new_count * data->size);
    memset((char *)data->data + data->size * new_count, 0, data->size * (data->maximum_count - new_count));

    data->actual_count = new_count;
    data->count = new_count;
    data->first_free_absolute_index = new_count;

    free(new_data);
}

static void datum_initialize(
    struct data_array *data,
    struct datum_header *header)
{
    assert(header);

    memset(header, 0, data->size);
    
    header->identifier = data->next_identifier;
    
    if (++data->next_identifier == NONE)
        data->next_identifier = (int16_t)DATUM_BASE_IDENTIFIER;
}
