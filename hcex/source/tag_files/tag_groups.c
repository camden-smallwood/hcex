#include "cseries/cseries.h"
#include "tag_files/tag_groups.h"

/* ---------- public code */

char *tag_data_get_pointer(
    const struct tag_data *data,
    size_t offset,
    size_t size)
{
    assert(size >= 0);
    assert(offset >= 0 && offset + size <= data->size);

    return (char *)data->address + offset;
}

char *tag_block_get_element_with_size(
    const struct tag_block *block,
    intptr_t index,
    size_t element_size)
{
    assert(block);
    assert(block->count >= 0);
    assert(!block->definition || block->definition->element_size == element_size);
    
    vassert(
        index >= 0 && index < block->count,
        "#%d is not a valid %s index in [#0,#%d)",
        index,
        block->definition ? block->definition->name : "<unknown>",
        block->count);
    
    assert(block->address);

    return (char *)block->address + element_size * index;
}
