#pragma once

/* ---------- macros */

#define DATUM_INDEX_NEW(identifier, absolute_index) \
    (((((int32_t)(identifier)) & UINT16_MAX) << 16) | (((int32_t)(absolute_index)) & UINT16_MAX))

#define DATUM_INDEX_GET_ABSOLUTE_INDEX(x) \
    ((int16_t)(((int32_t)(x)) & UINT16_MAX))

#define DATUM_INDEX_GET_IDENTIFIER(x) \
    ((int16_t)((((int32_t)(x)) >> 16) & UINT16_MAX))

/* ---------- constants */

enum
{
    DATA_ARRAY_SIGNATURE = 'd@t@',
    DATA_ITERATOR_SIGNATURE = 'iter',
    DATUM_BASE_IDENTIFIER = INT16_MAX + 1,
};

/* ---------- structures */

struct datum_header
{
    int16_t identifier;
};

struct data_array
{
    char name[32];
    int16_t maximum_count;
    int16_t size;
    bool valid;
    bool identifier_zero_invalid;
    tag signature;
    int16_t first_free_absolute_index;
    int16_t count;
    int16_t actual_count;
    int16_t next_identifier;
    void *data;
};

struct data_iterator
{
    struct data_array *data;
    int16_t absolute_index;
    int32_t index;
    tag signature;
};

/* ---------- prototypes/DATA.C */

void data_verify(struct data_array *data);
struct data_array *data_new(const char *name, int16_t maximum_count, int16_t size);
size_t data_allocation_size(int16_t maximum_count, int16_t size);
void data_initialize(struct data_array *data, const char *name, int16_t maximum_count, int16_t size);
void data_dispose(struct data_array *data);
void data_make_valid(struct data_array *data);
void data_make_invalid(struct data_array *data);
int32_t datum_new_at_index(struct data_array *data, int32_t index);
int32_t datum_new_at_plain_index_hack_for_player_data(struct data_array *data, int32_t index);
int32_t datum_new(struct data_array *data);
void datum_delete(struct data_array *data, int32_t index);
void data_delete_all(struct data_array *data);
void data_iterator_new(struct data_iterator *iterator, struct data_array *data);
void *data_iterator_next(struct data_iterator *iterator);
int32_t data_next_index(struct data_array *data, int32_t index);
int32_t data_prev_index(struct data_array *data, int32_t index);
void *datum_try_and_get(struct data_array *data, int32_t index);
void *datum_get(struct data_array *data, int32_t index);
