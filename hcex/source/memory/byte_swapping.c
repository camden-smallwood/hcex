#include "cseries/cseries.h"
#include "memory/byte_swapping.h"

/* ---------- definitions */

static intptr_t byte_bs_codes[] = {
    _begin_bs_array,
    _1byte,
    _1byte,
    _end_bs_array,
};

struct byte_swap_definition byte_bs_definition = {
    .name = "uint8_t",
    .size = 1,
    .codes = byte_bs_codes,
    .signature = BYTE_SWAP_DEFINITION_SIGNATURE,
};

static intptr_t word_bs_codes[] = {
    _begin_bs_array,
    _1byte,
    _2byte,
    _end_bs_array,
};

struct byte_swap_definition word_bs_definition = {
    .name = "uint16_t",
    .size = 2,
    .codes = word_bs_codes,
    .signature = BYTE_SWAP_DEFINITION_SIGNATURE,
};

static intptr_t long_bs_codes[] = {
    _begin_bs_array,
    _1byte,
    _4byte,
    _end_bs_array,
};

struct byte_swap_definition long_bs_definition = {
    .name = "long",
    .size = 4,
    .codes = long_bs_codes,
    .signature = BYTE_SWAP_DEFINITION_SIGNATURE,
};

static intptr_t int64_bs_codes[] = {
    _begin_bs_array,
    _1byte,
    _8byte,
    _end_bs_array,
};

struct byte_swap_definition int64_bs_definition = {
    .name = "int64",
    .size = 8,
    .codes = int64_bs_codes,
    .signature = BYTE_SWAP_DEFINITION_SIGNATURE,
};

/* ---------- private prototypes */

static void _byte_swap_data(
    struct byte_swap_definition *definition,
    char *data,
    intptr_t *codes,
    size_t *total_size_in_bytes,
    size_t *total_size_in_codes);

/* ---------- public code */

void byte_swap_data_explicit(
    char *name,
    size_t size,
    intptr_t *codes,
    size_t data_count,
    void *data)
{
    assert(codes);

    if (data == NULL || data_count == 0)
        return;

    struct byte_swap_definition definition = {
        .name = name,
        .size = size,
        .codes = codes,
        .verified = data != NULL,
        .signature = BYTE_SWAP_DEFINITION_SIGNATURE,
    };

    byte_swap_data(&definition, (char *)data, data_count);
}

size_t byte_swap_codes_size(
    char *name,
    intptr_t *codes)
{
    struct byte_swap_definition definition = {
        .name = name,
        .codes = codes,
        .size = 0,
        .signature = BYTE_SWAP_DEFINITION_SIGNATURE,
    };

    size_t size_in_bytes, size_in_codes;
    _byte_swap_data(&definition, 0, codes, &size_in_bytes, &size_in_codes);

    return size_in_bytes;
}

void byte_swap_data(
    struct byte_swap_definition *definition,
    char *data,
    size_t data_count)
{
    assert(definition);

    if (data == NULL)
        return;

    for (size_t i = 0; i < data_count; ++i)
        _byte_swap_data(
            definition,
            &data[i * definition->size],
            definition->codes,
            NULL,
            NULL);
}

void byte_swap_memory(
    void *memory,
    size_t count,
    intptr_t code)
{
    assert(memory);
    assert(count >= 0);
    assert(code == _2byte || code == _4byte || code == _8byte);

    for (size_t i = 0; i < count; i++)
    {
        switch (code)
        {
        case _2byte:
        {
            uint16_t value = ((uint16_t *)memory)[i];
            ((uint16_t *)memory)[i] = bswap16(value);
            break;
        }

        case _4byte:
        {
            uint32_t value = ((uint32_t *)memory)[i];
            ((uint32_t *)memory)[i] = bswap32(value);
            break;
        }

        case _8byte:
        {
            uint64_t value = ((uint64_t *)memory)[i];
            ((uint64_t *)memory)[i] = bswap64(value);
            break;
        }
        }
    }
}

/* ---------- private code */

static void _byte_swap_data(
    struct byte_swap_definition *definition,
    char *data,
    intptr_t *codes,
    size_t *total_size_in_bytes,
    size_t *total_size_in_codes)
{
    vassert(
        definition->signature == BYTE_SWAP_DEFINITION_SIGNATURE,
        "%s bs data has bad signature",
        definition->name);

    vassert(
        codes[0] == _begin_bs_array,
        "%s bs data @%p.#0 has bad start #%d",
        definition->name,
        codes,
        definition->codes[0]);

    vassert(
        codes[1] >= 0,
        "%s bs data @%p.#1 has invalid array size #%d",
        definition->name,
        codes,
        codes[1]);

    size_t i = 2;

    size_t size_in_bytes = 0;
    size_t size_in_codes = 0;

    while (true)
    {
        switch (codes[i])
        {
        case _2byte:
            if (data)
            {
                uint16_t value = *(uint16_t *)&data[size_in_bytes];
                *(uint16_t *)&data[size_in_bytes] = bswap16(value);
            }
            ++i;
            size_in_bytes += 2;
            break;

        case _4byte:
            if (data)
            {
                uint32_t value = *(uint32_t *)&data[size_in_bytes];
                *(uint32_t *)&data[size_in_bytes] = bswap32(value);
            }
            ++i;
            size_in_bytes += 4;
            break;

        case _8byte:
            if (data)
            {
                uint64_t value = *(uint64_t *)&data[size_in_bytes];
                *(uint64_t *)&data[size_in_bytes] = bswap64(value);
            }
            ++i;
            size_in_bytes += 8;
            break;

        case _begin_bs_array:
        {
            char *inner_data = data ? &data[size_in_bytes] : NULL;
            size_t inner_size_in_bytes = 0;
            size_t inner_size_in_codes = 0;

            _byte_swap_data(definition, inner_data, &codes[i], &inner_size_in_bytes, &inner_size_in_codes);

            i += inner_size_in_codes;
            size_in_bytes += inner_size_in_bytes;
            break;
        }

        case _end_bs_array:
        {
            size_in_codes = i + 1;
            
            if (--codes[1])
            {
                i = 2;
                continue;
            }

            if (total_size_in_bytes)
                *total_size_in_bytes = size_in_bytes;

            if (total_size_in_codes)
                *total_size_in_codes = size_in_codes;
            
            return;
        }

        case _extern_bs_definition:
        {
            char *inner_data = data ? &data[size_in_bytes] : NULL;
            size_t inner_size_in_bytes = 0;

            _byte_swap_data(
                (struct byte_swap_definition *)codes[i + 1],
                inner_data,
                *(intptr_t **)(codes[i + 1] + 8),
                &inner_size_in_bytes,
                NULL);
            
            i += 2;
            size_in_bytes += inner_size_in_bytes;
            break;
        }

        default:
            vassert(
                codes[i] > 0,
                "%s bs @%p.#%d has invalid code #%d",
                definition->name,
                codes,
                i,
                codes[i]);

            ++i;
            size_in_bytes += codes[i];
            break;
        }
    }
}
