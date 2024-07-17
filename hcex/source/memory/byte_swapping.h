#pragma once

/* ---------- macros */

#if __has_builtin(__builtin_bswap16)
#   define bswap16(x) __builtin_bswap16(x)
#else
#   define bswap16(x) \
        (((((x) >> 0) & 0xFF) << 8) | \
         ((((x) >> 8) & 0xFF) << 0))
#endif

#if __has_builtin(__builtin_bswap32)
#   define bswap32(x) __builtin_bswap32(x)
#else
#   define bswap32(x) \
        (((((x) >> 0) & 0xFF) << 24) | \
         ((((x) >> 8) & 0xFF) << 16) | \
         ((((x) >> 16) & 0xFF) << 8) | \
         ((((x) >> 24) & 0xFF) << 0))
#endif

#if __has_builtin(__builtin_bswap64)
#   define bswap64(x) __builtin_bswap64(x)
#else
#   define bswap64(x) \
        (((((x) >> 0) & 0xFF) << 56) | \
         ((((x) >> 8) & 0xFF) << 48) | \
         ((((x) >> 16) & 0xFF) << 40) | \
         ((((x) >> 24) & 0xFF) << 32) | \
         ((((x) >> 32) & 0xFF) << 24) | \
         ((((x) >> 40) & 0xFF) << 16) | \
         ((((x) >> 48) & 0xFF) << 8) | \
         ((((x) >> 56) & 0xFF) << 0))
#endif

/* ---------- constants */

enum
{
    _1byte = 1,
    _2byte= -2,
    _4byte= -4,
    _8byte = -8,
    _begin_bs_array = -100,
    _end_bs_array = -101,
    _extern_bs_definition = -102,
    BYTE_SWAP_DEFINITION_SIGNATURE = 'bysw',
};

/* ---------- structures */

struct byte_swap_definition
{
    char *name;
    size_t size;
    intptr_t *codes;
    tag signature;
    bool verified;
};

/* ---------- variables */

extern struct byte_swap_definition byte_bs_definition;
extern struct byte_swap_definition word_bs_definition;
extern struct byte_swap_definition long_bs_definition;
extern struct byte_swap_definition int64_bs_definition;

/* ---------- prototypes/BYTE_SWAPPING.C */

void byte_swap_data_explicit(char *name, size_t size, intptr_t *codes, size_t data_count, void *data);
size_t byte_swap_codes_size(char *name, intptr_t *codes);
void byte_swap_data(struct byte_swap_definition *definition, char *data, size_t data_count);
void byte_swap_memory(void *memory, size_t count, intptr_t code);
