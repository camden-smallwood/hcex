#include "projects/code/hcex/sources/memory/sl_list.h"
#include "projects/code/hcex/sources/memory/texture_page.h"
#include "projects/code/hcex/sources/cseries/cseries.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/stdio.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/time.inl"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/pshpack4.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/poppack.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/basetsd.h"
#include "projects/code/hcex/sources/memory/circular_queue.h"
#include "projects/code/hcex/sources/math/integer_math.h"
#include "projects/code/hcex/sources/memory/lrar_cache.h"
#include "projects/code/hcex/sources/memory/hashtable.h"
#include "projects/code/hcex/sources/memory/byte_swapping.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/pshpack8.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/stdlib.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/limits.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/winbase.h"
#include "projects/code/hcex/sources/memory/data_packets.h"
#include "projects/code/hcex/sources/cseries/progress.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/guiddef.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/stddef.h"
#include "projects/code/hcex/sources/memory/crc.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/math.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/pshpack2.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/string.h"
#include "projects/code/hcex/sources/math/real_math.h"
#include "projects/code/hcex/sources/bitmaps/bitmaps.h"
#include "projects/code/hcex/sources/memory/data_encoding.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/float.h"
#include "projects/code/hcex/sources/tag_files/files.h"
#include "projects/code/hcex/sources/memory/array.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/crtwrn.h"
#include "projects/code/hcex/sources/cseries/platform.h"
#include "projects/code/hcex/sources/bitmaps/bitmap_group.h"
#include "projects/code/hcex/sources/cseries/cseries_windows.h"
#include "projects/code/hcex/sources/tag_files/tag_groups.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/xdk.h"
#include "projects/code/hcex/sources/tag_files/tag_files.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/windef.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/vadefs.h"
#include "projects/code/hcex/sources/memory/stack_memory_pool.h"
#include "projects/code/hcex/sources/cache/cache_files.h"
#include "projects/code/hcex/sources/memory/lru_cache.h"
#include "projects/code/hcex/sources/cseries/errors.h"
#include "projects/code/hcex/sources/memory/data.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/winerror.h"
#include "projects/code/hcex/sources/math/geometry.h"
#include "projects/code/hcex/sources/bitmaps/bitmap_drawing.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/swprintf.inl"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/winnt.h"
#include "projects/code/hcex/sources/memory/lra_cache.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/ctype.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/malloc.h"
#include "projects/code/hcex/sources/halo_defines.h"
#include "projects/code/hcex/sources/cseries/headers.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/time.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/crtdefs.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/sal.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/codeanalysis/sourceannotations.h"
#include "projects/code/hcex/sources/math/periodic_functions.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/wtime.inl"

typedef void * * handle;
typedef long time_t;
void * * pool_new_handle(stack_memory_pool * pool, unsigned long size)// 0x8383F778
{
$M15359:
    stack_memory_pool * pool; // r4
    unsigned long size; // r5
}
void * * pool_new_handle_clear(stack_memory_pool * pool, unsigned long size)// 0x8383F820
{
$M15385:
    stack_memory_pool * pool; // r4
    unsigned long size; // r5
}
unsigned char pool_resize_handle(stack_memory_pool * pool, void * * * h, unsigned long new_size)// 0x8383F8C8
{
$M15449:
    stack_memory_pool * pool; // r4
    void * * * h; // r5
    unsigned long new_size; // r6
}
void dispose_handle(stack_memory_pool * pool, void * * h)// 0x8383F0E8
{
$M15090:
    stack_memory_pool * pool; // r4
    void * * h; // r5
}
void lock_handle(stack_memory_pool * pool, void * * * h)// 0x8383F138
{
    stack_memory_pool * pool; // r4
    void * * * h; // r5
}
void unlock_handle(stack_memory_pool * pool, void * * h)// 0x8383F158
{
    stack_memory_pool * pool; // r4
    void * * h; // r5
}
void * pool_new_pointer(stack_memory_pool * pool, unsigned long size)// 0x8383FA10
{
$M15485:
    stack_memory_pool * pool; // r4
    unsigned long size; // r5
}
void * pool_new_pointer_clear(stack_memory_pool * pool, unsigned long size)// 0x8383FAC8
{
$M15528:
    stack_memory_pool * pool; // r4
    unsigned long size; // r5
}
void * pool_resize_pointer(stack_memory_pool * pool, void * p, unsigned long new_size)// 0x8383FB80
{
$M15570:
    stack_memory_pool * pool; // r4
    void * p; // r5
    unsigned long new_size; // r6
}
void dispose_pointer(stack_memory_pool * pool, void * p)// 0x8383F1C8
{
$M15131:
    stack_memory_pool * pool; // r4
    void * p; // r5
}
void stack_memory_pool_reset(stack_memory_pool * pool)// 0x8383ED78
{
$M14991:
    stack_memory_pool * pool; // r4
}
unsigned char memory_block_valid(memory_block * block)// 0x8383F220
{
    memory_block * block; // r4
}
void memory_block_lock(memory_block * block)// 0x8383EDD8
{
    memory_block * block; // r4
}
void memory_block_unlock(memory_block * block)// 0x8383EDE8
{
    memory_block * block; // r4
}
unsigned char memory_block_is_locked(memory_block * block)// 0x8383EDF8
{
    memory_block * block; // r4
}
void memory_block_set_size_and_index(memory_block * block, unsigned long new_size, unsigned long index)// 0x8383EE08
{
    memory_block * block; // r4
    unsigned long new_size; // r5
    unsigned long index; // r6
}
unsigned long memory_block_get_real_size(memory_block * block)// 0x8383EE18
{
    memory_block * block; // r4
}
unsigned long memory_block_get_user_size(memory_block * block)// 0x8383EE28
{
    memory_block * block; // r4
}
void * memory_block_get_user_address(memory_block * block)// 0x8383EE38
{
    memory_block * block; // r4
}
unsigned long memory_block_get_pool_index(memory_block * block)// 0x8383EE40
{
    memory_block * block; // r4
}
memory_block * stack_memory_pool_new_block(stack_memory_pool * pool, unsigned long size)// 0x8383F678
{
    stack_memory_pool * pool; // r4
    unsigned long size; // r5
}
memory_block * stack_memory_pool_new_block_clear(stack_memory_pool * pool, unsigned long size)// 0x8383F680
{
$M15307:
    stack_memory_pool * pool; // r4
    unsigned long size; // r5
}
memory_block * stack_memory_pool_resize_block(stack_memory_pool * pool, memory_block * reference, unsigned long new_size)// 0x8383F6D8
{
$M15340:
    stack_memory_pool * pool; // r4
    memory_block * reference; // r5
    unsigned long new_size; // r6
}
void stack_memory_pool_dispose_block(stack_memory_pool * pool, memory_block * reference)// 0x8383EE48
{
    stack_memory_pool * pool; // r4
    memory_block * reference; // r5
}
void * stack_memory_pool_lock_block(stack_memory_pool * reference, memory_block *)// 0x8383EEC8
{
    stack_memory_pool * pool; // r2 offset 16
    memory_block * reference; // r4
}
void stack_memory_pool_unlock_block(stack_memory_pool * reference, memory_block *)// 0x8383EEE0
{
    stack_memory_pool * pool; // r2 offset 16
    memory_block * reference; // r4
}
unsigned long stack_memory_pool_free_space_at_end_of_pool(stack_memory_pool * pool)// 0x8383EEF0
{
    stack_memory_pool * pool; // r4
}
long stack_memory_pool_find_first_unused_memory_block(stack_memory_pool * pool)// 0x8383EF28
{
    stack_memory_pool * pool; // r4
}
void stack_memory_pool_set_next_block_index(stack_memory_pool * pool)// 0x8383EF70
{
    stack_memory_pool * pool; // r4
}
memory_block * stack_memory_pool_allocate(stack_memory_pool * pool, unsigned long size)// 0x8383F248
{
$M15270:
    stack_memory_pool * pool; // r4
    unsigned long size; // r5
}
void stack_memory_pool_compact(stack_memory_pool * pool)// 0x8383EFD0
{
$M15065:
    stack_memory_pool * pool; // r4
}
unsigned char stack_memory_pool_valid_block(stack_memory_pool * pool, memory_block * block)// 0x8383F5C8
{
    stack_memory_pool * pool; // r4
    memory_block * block; // r5
}
void * stack_memory_pool_find_space_between_blocks(stack_memory_pool * pool, unsigned long size, memory_block * * free_space_in_pool_previous)// 0x8383F070
{
    stack_memory_pool * pool; // r4
    unsigned long size; // r5
    memory_block * * free_space_in_pool_previous; // r6
}