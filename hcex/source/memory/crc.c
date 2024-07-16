#include "cseries/cseries.h"
#include "memory/crc.h"

/* ---------- private variables */

static uint32_t crc_table[256];
static bool crc_table_built = false;

/* ---------- private prototypes */

static void build_crc_table(uint32_t *crc_table);

/* ---------- public code */

void crc_new(
    uint32_t *crc_reference)
{
    // TODO: asserts
    
    *crc_reference = NONE;
}

void crc_checksum_buffer(
    uint32_t *crc_reference,
    const void *buffer,
    size_t buffer_size)
{
    // TODO: asserts
    
    if (!crc_table_built)
    {
        build_crc_table(crc_table);
        crc_table_built = true;
    }

    uint32_t v8 = *crc_reference;

    if (buffer_size > 0)
    {
        size_t remaining_buffer_size = buffer_size;
        char *v10 = (char *)buffer - 1;

        do
        {
            v8 = (v8 >> 8) ^ *(uint32_t *)((char *)crc_table + ((sizeof(uint32_t) * ((uint8_t)*++v10 ^ v8)) & 0x3FC));
            --remaining_buffer_size;
        } while (remaining_buffer_size);
    }

    *crc_reference = v8;
}

/* ---------- private code */

static void build_crc_table(
    uint32_t *crc_table)
{
    // TODO: asserts
    
    for (uint32_t i = 0; i < 256; i++)
    {
        uint32_t crc_word = i;

        for (uint32_t j = 0; j < 8; j++)
        {
            bool crc_word_bit_set = TEST_FLAG(crc_word, 0);
            crc_word >>= 1;
            
            if (crc_word_bit_set)
            {
                crc_word ^= 0xEDB88320;
            }
        }

        crc_table[i] = crc_word;
    }
}
