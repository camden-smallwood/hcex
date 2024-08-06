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
#include "projects/code/hcex/sources/memory/lruv_cache.h"
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

typedef void(*lruv_header_proc)(_iobuf *);
typedef const char *(*lruv_name_block_proc)(long);
typedef long time_t;
lruv_cache * lruv_new(const char * name, long page_count, long page_size_bits, long maximum_block_count, void(*delete_block_proc)(long), unsigned char(*locked_block_proc)(long))// 0x837A9140
{
$M14843:
    const char * name; // r4
    long page_count; // r5
    long page_size_bits; // r6
    long maximum_block_count; // r7
    void(*delete_block_proc)(long); // r8
    unsigned char(*locked_block_proc)(long); // r9
}
long lruv_allocation_size(long maximum_block_count)// 0x837A8C50
{
$M14755:
    long maximum_block_count; // r4
}
void lruv_initialize(lruv_cache * cache, const char * name, long page_count, long page_size_bits, long maximum_block_count, void(*delete_block_proc)(long), unsigned char(*locked_block_proc)(long))// 0x837A8C80
{
$M14764:
    lruv_cache * cache; // r4
    const char * name; // r5
    long page_count; // r6
    long page_size_bits; // r7
    long maximum_block_count; // r8
    void(*delete_block_proc)(long); // r9
    unsigned char(*locked_block_proc)(long); // r10
}
void lruv_update_function_pointers(lruv_cache * cache, void(*delete_block_proc)(long), unsigned char(*locked_block_proc)(long))// 0x837A8D20
{
    lruv_cache * cache; // r4
    void(*delete_block_proc)(long); // r5
    unsigned char(*locked_block_proc)(long); // r6
}
void lruv_delete(lruv_cache * cache)// 0x837A8D30
{
$M14772:
    lruv_cache * cache; // r4
}
void lruv_idle(lruv_cache * cache)// 0x837A8D70
{
    lruv_cache * cache; // r4
}
void lruv_flush(lruv_cache * cache)// 0x837A91B8
{
$M14863:
    lruv_cache * cache; // r4
    data_iterator iterator; // r2 offset 80
}
long lruv_block_new(lruv_cache * cache, long size)// 0x837A92A0
{
$M14896:
    lruv_cache * cache; // r4
    long size; // r5
    lruv_cache_hole best_hole; // r2 offset 80
    unsigned long oldest_block_last_used_frame_index; // r2 offset 112
    lruv_cache_hole holes[256]; // r2 offset 128
    data_iterator iterator; // r2 offset 96
}
void lruv_block_delete(lruv_cache * cache, long block_index)// 0x837A8D80
{
$M14782:
    lruv_cache * cache; // r4
    long block_index; // r5
}
void lruv_block_touch(lruv_cache * cache, long block_index)// 0x837A8E50
{
    lruv_cache * cache; // r4
    long block_index; // r5
}
unsigned long lruv_block_get_address(lruv_cache * cache, long block_index)// 0x837A8E70
{
    lruv_cache * cache; // r4
    long block_index; // r5
}
unsigned char lruv_block_touched(lruv_cache * cache, long block_index)// 0x837A8E98
{
    lruv_cache * cache; // r4
    long block_index; // r5
}
int32_t lruv_cache_get_page_allocated(lruv_cache * cache)// 0x837A8EC8
{
$M14797:
    lruv_cache * cache; // r4
    data_iterator iterator; // r2 offset 80
}
void lruv_cache_get_page_usage(lruv_cache * cache, unsigned char * page_usage)// 0x837A8F30
{
$M14807:
    lruv_cache * cache; // r4
    unsigned char * page_usage; // r5
    data_iterator iterator; // r2 offset 80
}
void lruv_resize(lruv_cache * cache, long new_page_count)// 0x837A9000
{
$M14827:
    lruv_cache * cache; // r4
    long new_page_count; // r5
    data_iterator iterator; // r2 offset 80
}
unsigned char lruv_has_locked_proc(const lruv_cache * cache)// 0x837A9108
{
    const lruv_cache * cache; // r4
}
void lruv_debug_to_file(const char * path, const char * failed_allocation_name, long failed_allocation_size, lruv_cache * cache, void(*header_proc)(_iobuf *), const char *(*name_block_proc)(long))// 0x837A96C8
{
$M14919:
    const char * path; // r4
    const char * failed_allocation_name; // r5
    long failed_allocation_size; // r6
    lruv_cache * cache; // r7
    void(*header_proc)(_iobuf *); // r8
    const char *(*name_block_proc)(long); // r9
}
long lruv_cache_bytes_to_pages(lruv_cache * cache, long size_in_bytes)// 0x837A9118
{
    lruv_cache * cache; // r4
    long size_in_bytes; // r5
}