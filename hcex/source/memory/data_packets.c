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
void data_packet_verify(data_packet_definition * packet_definition)// 0x83896D10
{
$M14617:
    data_packet_definition * packet_definition; // r4
    short byte_count; // r2 offset 82
    short field_count; // r2 offset 80
}
unsigned char data_packet_encode(data_packet_definition * packet_definition, short version, void * packet, void * buffer, short * buffer_size, short maximum_buffer_size)// 0x83896D60
{
$M14629:
    data_packet_definition * packet_definition; // r4
    short version; // r5
    void * packet; // r6
    void * buffer; // r7
    short * buffer_size; // r8
    short maximum_buffer_size; // r9
    data_encoding_state encode_state; // r2 offset 96
    unsigned char temp; // r2 offset 80
}
unsigned char data_packet_decode(data_packet_definition * packet_definition, void * encoded_packet, short encoded_packet_size, void * decoded_packet, short * version_reference, short * actual_encoded_packet_size_reference)// 0x83896E30
{
$M14646:
    data_packet_definition * packet_definition; // r4
    void * encoded_packet; // r5
    short encoded_packet_size; // r6
    void * decoded_packet; // r7
    short * version_reference; // r8
    short * actual_encoded_packet_size_reference; // r9
    data_encoding_state decode_state; // r2 offset 96
}
void _data_packet_verify(data_packet_definition * packet_definition, short * byte_count_reference, data_packet_field * first_field, short * field_count_reference)// 0x83896560
{
$M14581:
    data_packet_definition * packet_definition; // r4
    short * byte_count_reference; // r5
    data_packet_field * first_field; // r6
    short * field_count_reference; // r7
    short size; // r2 offset 82
    short byte_count; // r2 offset 82
    short field_count; // r2 offset 80
}
void _data_packet_encode(data_packet_definition * packet_definition, data_encoding_state * encode_state, short version, void * original_buffer, short * byte_count_reference, data_packet_field * first_field, short * field_count_reference)// 0x83896718
{
$M14594:
    data_packet_definition * packet_definition; // r4
    data_encoding_state * encode_state; // r5
    short version; // r6
    void * original_buffer; // r7
    short * byte_count_reference; // r8
    data_packet_field * first_field; // r9
    short * field_count_reference; // r10
    short byte_count; // r2 offset 82
    short field_count; // r2 offset 84
    unsigned char temp; // r2 offset 80
}
void _data_packet_decode(data_packet_definition * packet_definition, data_encoding_state * decode_state, short version, void * original_buffer, short * byte_count_reference, data_packet_field * first_field, short * field_count_reference)// 0x83896A08
{
$M14611:
    data_packet_definition * packet_definition; // r4
    data_encoding_state * decode_state; // r5
    short version; // r6
    void * original_buffer; // r7
    short * byte_count_reference; // r8
    data_packet_field * first_field; // r9
    short * field_count_reference; // r10
    short byte_count; // r2 offset 80
    short field_count; // r2 offset 82
}