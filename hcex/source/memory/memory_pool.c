#include "cseries/cseries.h"
#include "memory/memory_pool.h"

#include <stdlib.h>
#include <string.h>

/* ---------- private prototypes */

static void memory_pool_verify(struct memory_pool *pool);

/* ---------- public code */

struct memory_pool *memory_pool_new(
    const char *name,
    size_t size)
{
    struct memory_pool *pool = malloc(memory_pool_allocation_size(size));

    if (pool)
        memory_pool_initialize(pool, name, size);

    return pool;
}

void memory_pool_delete(
    struct memory_pool *pool)
{
    memory_pool_verify(pool);
    memset(pool, 0, sizeof(*pool));
    free(pool);
}

size_t memory_pool_allocation_size(
    size_t size)
{
    return size + sizeof(struct memory_pool);
}

void memory_pool_initialize(
    struct memory_pool *pool,
    const char *name,
    size_t size)
{
    assert(pool);
    assert(name);

    memset(pool, 0, sizeof(struct memory_pool));

    pool->signature = POOL_SIGNATURE;
    strncpy(pool->name, name, sizeof(pool->name) - 1);
    pool->base_address = &pool[1];
    pool->size = size;
    pool->free_size = size;
    pool->first_block = 0;
    pool->last_block = 0;
}

struct memory_pool_block *memory_pool_block_get(
    struct memory_pool *pool,
    void **reference)
{
    assert(reference && (*reference));

    memory_pool_verify(pool);
    void **expected_reference = (void **)*((uintptr_t *)*reference - sizeof(void *));

    vassert(
        expected_reference == reference,
        "expected reference %p but got %p",
        expected_reference,
        reference);

    struct memory_pool_block *other_block = pool->first_block;
    assert(other_block);

    while (other_block != (struct memory_pool_block *)((uint8_t *)*reference - sizeof(struct memory_pool_block)))
    {
        other_block = other_block->next_block;
        assert(other_block);
    }

    return (struct memory_pool_block *)((uint8_t *)*reference - sizeof(struct memory_pool_block));
}

bool memory_pool_block_allocate(
    struct memory_pool *pool,
    void **reference,
    size_t size)
{
    size_t block_size = memory_pool_block_compute_actual_size(size);

    memory_pool_verify(pool);

    struct memory_pool_block *last_block = pool->last_block;

    struct memory_pool_block *block =
        last_block
            ? (struct memory_pool_block *)((uint8_t *)last_block + last_block->size)
            : (struct memory_pool_block *)pool->base_address;

    if ((uint8_t *)((uintptr_t)block + block_size) > (uint8_t *)pool->base_address + pool->size || !block)
        return false;

    block->size = block_size;
    block->header_signature = BLOCK_HEADER_SIGNATURE;
    block->reference = reference;
    block->next_block = NULL;
    block->previous_block = pool->last_block;
    block->trailer_signature = BLOCK_TRAILER_SIGNATURE;

    if (!pool->first_block)
        pool->first_block = block;

    if (last_block)
        last_block->next_block = block;

    pool->last_block = block;
    pool->free_size -= block_size;

    *reference = &block[1];

    return true;
}

bool memory_pool_block_reallocate(
    struct memory_pool *pool,
    void **reference,
    size_t new_size)
{
    struct memory_pool_block *block = memory_pool_block_get(pool, reference);
    size_t actual_new_size = memory_pool_block_compute_actual_size(new_size);

    struct memory_pool_block *next_block = block->next_block;

    if (!next_block)
        next_block = (struct memory_pool_block *)((uint8_t *)pool->base_address + pool->size);

    if ((struct memory_pool_block *)((uint8_t *)block + actual_new_size) > next_block)
    {
        void *new_buffer = NULL;

        if (!memory_pool_block_allocate(pool, &new_buffer, new_size))
            return false;

        assert(actual_new_size > block->size);
        memcpy(new_buffer, *reference, block->size - sizeof(struct memory_pool_block));
        memory_pool_block_free(pool, reference);
        memory_pool_block_get(pool, &new_buffer)->reference = reference;

        *reference = new_buffer;

        return true;
    }

    pool->free_size += (block->size - actual_new_size);
    assert(pool->free_size >= 0 && pool->free_size <= pool->size);

    block->size = actual_new_size;

    return true;
}

void memory_pool_block_free(
    struct memory_pool *pool,
    void **reference)
{
    struct memory_pool_block *block = memory_pool_block_get(pool, reference);

    pool->free_size += block->size;
    assert(pool->free_size <= pool->size);

    struct memory_pool_block *previous_block = block->previous_block;

    if (previous_block)
        previous_block->next_block = block->next_block;
    else
        pool->first_block = block->next_block;

    struct memory_pool_block *next_block = block->next_block;

    if (next_block)
        next_block->previous_block = block->previous_block;
    else
        pool->last_block = block->previous_block;

    memset(block, 0, block->size);
}

void memory_pool_compact(
    struct memory_pool *pool)
{
    struct memory_pool_block *block = pool->first_block;

    if (block)
    {
        struct memory_pool_block *last_block = (struct memory_pool_block *)pool->base_address;
        struct memory_pool_block *previous_block = NULL;

        do
        {
            if (block > last_block)
            {
                memmove(last_block, block, block->size);
                block = last_block;
                *last_block->reference = &last_block[1];
            }

            block->previous_block = previous_block;

            if (previous_block)
                previous_block->next_block = block;
            else
                pool->first_block = block;

            last_block = (struct memory_pool_block *)((uint8_t *)block + block->size);
            previous_block = block;
            block = block->next_block;
        } while (block);

        previous_block->next_block = NULL;
        pool->last_block = previous_block;
    }

    memory_pool_verify(pool);
}

size_t memory_pool_get_free_size(
    struct memory_pool *pool)
{
    return pool->free_size;
}

size_t memory_pool_get_used_size(
    struct memory_pool *pool)
{
    struct memory_pool_block *last_block = pool->last_block;

    return last_block ? ((size_t)last_block + last_block->size) - (size_t)pool->base_address : 0;
}

size_t memory_pool_get_contiguous_free_size(
    struct memory_pool *pool)
{
    struct memory_pool_block *last_block = pool->last_block;

    return last_block ? pool->size - (((size_t)last_block + last_block->size) - (size_t)pool->base_address) : pool->size;
}

size_t memory_pool_block_compute_actual_size(
    size_t size)
{
    size_t result = size + sizeof(struct memory_pool_block);

    return (result & 3) != 0 ? (result | 3) + 1 : result;
}

struct memory_pool_block *memory_pool_block_new(
    struct memory_pool *pool,
    size_t size)
{
    struct memory_pool_block *last_block = pool->last_block;

    uint8_t *base_address = last_block ? (uint8_t *)last_block + last_block->size : (uint8_t *)pool->base_address;

    if ((uint8_t *)pool->base_address + pool->size < base_address + size)
        return NULL;

    return (struct memory_pool_block *)base_address;
}

/* ---------- private code */

static void memory_pool_verify(
    struct memory_pool *pool)
{
    assert(pool->signature == POOL_SIGNATURE);
    assert(pool->size > 0);

    for (struct memory_pool_block
            *block = pool->first_block,
            *previous_block = NULL;

        block != NULL;

        previous_block = block,
        block = block->next_block)
    {
        assert(block->previous_block == previous_block);
        assert(block->next_block || pool->last_block == block);
        assert(block->header_signature == BLOCK_HEADER_SIGNATURE);
        assert(block->trailer_signature == BLOCK_TRAILER_SIGNATURE);
        assert((uint8_t *)block >= (uint8_t *)pool->base_address);
        assert((uint8_t *)block + block->size <= (uint8_t *)pool->base_address + pool->size);
    }
}
