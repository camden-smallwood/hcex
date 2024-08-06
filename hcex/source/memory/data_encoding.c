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

typedef long time_t;
void data_encode_new(data_encoding_state * state, void * buffer, long buffer_size)// 0x8389C8F0
{
    data_encoding_state * state; // r4
    void * buffer; // r5
    long buffer_size; // r6
}
unsigned char data_encode_memory(data_encoding_state * state, void * buffer, short count, long code)// 0x8389C910
{
$M14558:
    data_encoding_state * state; // r4
    void * buffer; // r5
    short count; // r6
    long code; // r7
    long size; // r2 offset 80
}
unsigned char data_encode_integer(data_encoding_state * state, long value, long maximum_value)// 0x8389CA30
{
$M14565:
    data_encoding_state * state; // r4
    long value; // r5
    long maximum_value; // r6
    unsigned char temp; // r2 offset 80
    short temp; // r2 offset 80
    long temp; // r2 offset 80
}
unsigned char data_encode_structures(data_encoding_state * state, void * source_structures, short structure_count, byte_swap_definition * bs_definition)// 0x8389CAB8
{
$M14571:
    data_encoding_state * state; // r4
    void * source_structures; // r5
    short structure_count; // r6
    byte_swap_definition * bs_definition; // r7
}
unsigned char data_encode_array(data_encoding_state * state, long element_count_size, void * source_array, long element_count, byte_swap_definition * bs_definition)// 0x8389CB58
{
$M14581:
    data_encoding_state * state; // r4
    long element_count_size; // r5
    void * source_array; // r6
    long element_count; // r7
    byte_swap_definition * bs_definition; // r8
    unsigned char temp; // r2 offset 80
    short temp; // r2 offset 80
    long temp; // r2 offset 80
    unsigned long long temp; // r2 offset 80
}
unsigned char data_encode_string(data_encoding_state * state, char * source_string, short maximum_string_length)// 0x8389CC38
{
$M14587:
    data_encoding_state * state; // r4
    char * source_string; // r5
    short maximum_string_length; // r6
}
void data_decode_new(data_encoding_state * state, void * buffer, long buffer_size)// 0x8389CCE0
{
    data_encoding_state * state; // r4
    void * buffer; // r5
    long buffer_size; // r6
}
void * data_decode_structures(data_encoding_state * state, short structure_count, byte_swap_definition * bs_definition)// 0x8389CD00
{
    data_encoding_state * state; // r4
    short structure_count; // r5
    byte_swap_definition * bs_definition; // r6
}
void * data_decode_memory(data_encoding_state * state, short count, long code)// 0x8389CD60
{
    data_encoding_state * state; // r4
    short count; // r5
    long code; // r6
    long size; // r2 offset -16
}
unsigned char data_decode_byte(data_encoding_state * state)// 0x8389CE20
{
$M14603:
    data_encoding_state * state; // r4
}
short data_decode_short(data_encoding_state * state)// 0x8389CE70
{
$M14611:
    data_encoding_state * state; // r4
}
long data_decode_long(data_encoding_state * state)// 0x8389CEC0
{
$M14619:
    data_encoding_state * state; // r4
}
unsigned long long data_decode_int64(data_encoding_state * state)// 0x8389CF08
{
$M14627:
    data_encoding_state * state; // r4
}
long data_decode_integer(data_encoding_state * state, long maximum_value)// 0x8389CF50
{
$M14649:
    data_encoding_state * state; // r4
    long maximum_value; // r5
}
void * data_decode_array(data_encoding_state * state, long element_count_size, long * element_count_reference, long maximum_element_count, byte_swap_definition * bs_definition)// 0x8389D010
{
$M14657:
    data_encoding_state * state; // r4
    long element_count_size; // r5
    long * element_count_reference; // r6
    long maximum_element_count; // r7
    byte_swap_definition * bs_definition; // r8
    long element_count; // r2 offset 80
}
char * data_decode_string(data_encoding_state * state, short maximum_string_length)// 0x8389D108
{
    data_encoding_state * state; // r4
    short maximum_string_length; // r5
}