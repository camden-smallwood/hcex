#include "cseries/cseries.h"
#include "tag_files/tag_groups.h"

/* ---------- public code */

char *tag_data_get_pointer(
    const struct tag_data *data,
    size_t offset,
    size_t size)
{
    // TODO: asserts
    
    return (char *)data->address + offset;
}

char *tag_block_get_element_with_size(
    const struct tag_block *block,
    intptr_t index,
    size_t element_size)
{
    // TODO: asserts

    return (char *)block->address + index * element_size;
}
