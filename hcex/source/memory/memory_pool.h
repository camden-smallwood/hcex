#pragma once

/* ---------- constants */

enum
{
    BLOCK_HEADER_SIGNATURE = 'head',
    BLOCK_TRAILER_SIGNATURE = 'tail',
    POOL_SIGNATURE = 'pool',
};

/* ---------- structures */

struct memory_pool
{
    tag signature;
    char name[32];
    void *base_address;
    size_t size;
    size_t free_size;
    struct memory_pool_block *first_block;
    struct memory_pool_block *last_block;
};

struct memory_pool_block
{
    tag header_signature;
    size_t size;
    void **reference;
    struct memory_pool_block *next_block;
    struct memory_pool_block *previous_block;
    tag trailer_signature;
};

/* ---------- prototypes/MEMORY_POOL.C */

struct memory_pool *memory_pool_new(const char *name, size_t size);
void memory_pool_delete(struct memory_pool *pool);

size_t memory_pool_allocation_size(size_t size);

void memory_pool_initialize(struct memory_pool *pool, const char *name, size_t size);

struct memory_pool_block *memory_pool_block_get(struct memory_pool *pool, void **reference);
bool memory_pool_block_allocate(struct memory_pool *pool, void **reference, size_t size);
bool memory_pool_block_reallocate(struct memory_pool *pool, void **reference, size_t new_size);

void memory_pool_block_free(struct memory_pool *pool, void **reference);
void memory_pool_compact(struct memory_pool *pool);

size_t memory_pool_get_free_size(struct memory_pool *pool);
size_t memory_pool_get_used_size(struct memory_pool *pool);
size_t memory_pool_get_contiguous_free_size(struct memory_pool *pool);
size_t memory_pool_block_compute_actual_size(size_t size);

struct memory_pool_block *memory_pool_block_new(struct memory_pool *pool, size_t size);
