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
#include "projects/code/hcex/sources/memory/bitstream.h"
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

const unsigned char s_zero_masks[9]; // 0x8212DDD0
const unsigned char s_one_masks[9]; // 0x8212DDDC
typedef long time_t;
unsigned char bitstream_initialize(bitstream_t * bit_stream, void * buffer, const uint32_t first_bit, const uint32_t bit_count, const bitstream_mode mode)// 0x8387BD38
{
    bitstream_t * bit_stream; // r4
    void * buffer; // r5
    const uint32_t first_bit; // r6
    const uint32_t bit_count; // r7
    bitstream_mode mode; // r8
}
unsigned char bitstream_dispose(bitstream_t * bit_stream)// 0x8387BBF8
{
    bitstream_t * bit_stream; // r4
}
unsigned char bitstream_has_bits(const bitstream_t * bit_stream, const uint32_t bit_count)// 0x8387BD70
{
    const bitstream_t * bit_stream; // r4
    const uint32_t bit_count; // r5
}
uint32_t bitstream_write_bit(bitstream_t * bit_stream, const uint32_t value)// 0x8387C3A8
{
$M15320:
    bitstream_t * bit_stream; // r4
    const uint32_t value; // r5
}
uint32_t bitstream_write_bits(bitstream_t * bit_stream, const void * value, const uint32_t bit_count)// 0x8387C458
{
$M15638:
    bitstream_t * bit_stream; // r4
    const void * value; // r5
    const uint32_t bit_count; // r6
}
uint32_t bitstream_read_bit(bitstream_t * bit_stream, unsigned char * value)// 0x8387C6B8
{
$M15689:
    bitstream_t * bit_stream; // r4
    unsigned char * value; // r5
}
uint32_t bitstream_read_bits(bitstream_t * bit_stream, void * value, const uint32_t bit_count)// 0x8387C758
{
$M15932:
    bitstream_t * bit_stream; // r4
    void * value; // r5
    const uint32_t bit_count; // r6
}
unsigned char bitstream_seek(bitstream_t * bit_stream, const int32_t offset, const bitstream_seek_origin origin)// 0x8387BDB0
{
    bitstream_t * bit_stream; // r4
    const int32_t offset; // r5
    bitstream_seek_origin origin; // r6
}
uint32_t bitstream_tell(const bitstream_t * bit_stream)// 0x8387BC28
{
    const bitstream_t * bit_stream; // r4
}
uint32_t bitstream_get_size(const bitstream_t * bit_stream)// 0x8387BB58
{
    const bitstream_t * bit_stream; // r4
}
uint32_t bitstream_get_bits_remaining(const bitstream_t * bit_stream)// 0x8387BC48
{
    const bitstream_t * bit_stream; // r4
}
void initialize_bitstream(bitstream_t * stream, unsigned char * buffer, const uint32_t first_bit, const uint32_t bit_count, const bitstream_mode mode)// 0x8387BC68
{
    bitstream_t * stream; // r4
    unsigned char * buffer; // r5
    const uint32_t first_bit; // r6
    const uint32_t bit_count; // r7
    bitstream_mode mode; // r8
}
void uninitialize_bitstream(bitstream_t * stream)// 0x8387BB60
{
    bitstream_t * stream; // r4
}
unsigned char has_bits(const bitstream_t * stream, const uint32_t bit_count)// 0x8387BC98
{
    const bitstream_t * stream; // r4
    const uint32_t bit_count; // r5
}
unsigned char advance_cursor(bitstream_t * stream, const uint32_t bit_count)// 0x8387BE68
{
    bitstream_t * stream; // r4
    const uint32_t bit_count; // r5
}
unsigned char set_cursor(bitstream_t * stream, const uint32_t bit_position)// 0x8387BCD8
{
    bitstream_t * stream; // r4
    const uint32_t bit_position; // r5
}
unsigned char write_bit(bitstream_t * stream, const uint32_t value)// 0x8387BED8
{
$M14982:
    bitstream_t * stream; // r4
    const uint32_t value; // r5
}
unsigned char write_bits(bitstream_t * stream, const uint32_t value, const uint32_t bit_count)// 0x8387BFA0
{
$M15137:
    bitstream_t * stream; // r4
    const uint32_t value; // r5
    const uint32_t bit_count; // r6
}
const uint32_t read_bit(bitstream_t * stream, unsigned char * value)// 0x8387C150
{
$M15169:
    bitstream_t * stream; // r4
    unsigned char * value; // r5
}
const uint32_t read_bits(bitstream_t * stream, const uint32_t bit_count, uint32_t * value)// 0x8387C1F0
{
$M15267:
    bitstream_t * stream; // r4
    const uint32_t bit_count; // r5
    uint32_t * value; // r6
    uint32_t dest; // r2 offset 80
}
const uint32_t absolute_bit_position_current(const bitstream_t * stream)// 0x8387BB88
{
    const bitstream_t * stream; // r4
}
void bit_byte_position_from_absolute_bit_position(const uint32_t bit_position, uint32_t * bit_in_byte, uint32_t * byte_number)// 0x8387BBA0
{
    const uint32_t bit_position; // r4
    uint32_t * bit_in_byte; // r5
    uint32_t * byte_number; // r6
}
unsigned char valid_bit_position(const bitstream_t * stream, const uint32_t bit_position)// 0x8387BBB8
{
    const bitstream_t * stream; // r4
    const uint32_t bit_position; // r5
}
unsigned char is_bit_position_end_of_stream(const bitstream_t * stream, const uint32_t bit_position)// 0x8387BBE0
{
    const bitstream_t * stream; // r4
    const uint32_t bit_position; // r5
}