#include "projects/code/hcex/sources/physics/breakable_surfaces.h"
#include "projects/code/hcex/sources/memory/sl_list.h"
#include "projects/code/hcex/sources/memory/texture_page.h"
#include "projects/code/hcex/sources/cseries/cseries.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/stdio.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/time.inl"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/pshpack4.h"
#include "projects/code/hcex/sources/sound/sound_environment_definitions.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/poppack.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/basetsd.h"
#include "projects/code/hcex/sources/memory/circular_queue.h"
#include "projects/code/hcex/sources/math/integer_math.h"
#include "projects/code/hcex/sources/memory/lrar_cache.h"
#include "projects/code/hcex/sources/game/game_globals.h"
#include "projects/code/hcex/sources/objects/damage.h"
#include "projects/code/hcex/sources/memory/hashtable.h"
#include "projects/code/hcex/sources/memory/byte_swapping.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/pshpack8.h"
#include "projects/code/hcex/sources/interface/player_ui.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/xcompress.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/stdlib.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/limits.h"
#include "projects/code/hcex/sources/memory/lruv_cache.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/winbase.h"
#include "projects/code/hcex/sources/text/text_group.h"
#include "projects/code/hcex/sources/text/unicode.h"
#include "projects/code/hcex/sources/memory/data_packets.h"
#include "projects/code/hcex/sources/cseries/progress.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/guiddef.h"
#include "projects/code/hcex/sources/bungie_net/common/message_header.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/stddef.h"
#include "projects/code/hcex/sources/memory/crc.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/math.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/pshpack2.h"
#include "projects/code/hcex/sources/sound/sound_manager.h"
#include "projects/code/hcex/sources/scenario/scenario.h"
#include "projects/code/hcex/sources/scenario/scenario_definitions.h"
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
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/xbox.h"
#include "projects/code/hcex/sources/cache/cache_files.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/xconfig.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/xinputdefs.h"
#include "projects/code/hcex/sources/memory/lru_cache.h"
#include "projects/code/hcex/sources/cseries/errors.h"
#include "projects/code/hcex/sources/interface/interface.h"
#include "projects/code/hcex/sources/memory/data.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/winerror.h"
#include "projects/code/hcex/sources/math/geometry.h"
#include "projects/code/hcex/sources/bitmaps/bitmap_drawing.h"
#include "projects/code/hcex/sources/cache/physical_memory_map.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/swprintf.inl"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/winnt.h"
#include "projects/code/hcex/sources/networking/network_game_globals.h"
#include "projects/code/hcex/sources/memory/lra_cache.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/ctype.h"
#include "projects/code/hcex/sources/memory/bitstream.h"
#include "projects/code/hcex/sources/ai/ai_scenario_definitions.h"
#include "projects/code/hcex/sources/game/game.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/malloc.h"
#include "projects/code/hcex/sources/game/cheats.h"
#include "projects/code/hcex/sources/halo_defines.h"
#include "projects/code/hcex/sources/cseries/headers.h"
#include "projects/code/hcex/sources/saved games/game_state.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/time.h"
#include "projects/code/hcex/sources/memory/memory_pool.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/crtdefs.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/sal.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/codeanalysis/sourceannotations.h"
#include "projects/code/hcex/sources/math/periodic_functions.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/wtime.inl"

<unnamed-tag> xbox_game_state_globals; // 0x844CCBB8
typedef long time_t;
void * game_state_allocate_buffer(unsigned long address, unsigned long cpu_size, unsigned long gpu_size)// 0x837A7D08
{
$M19957:
    unsigned long address; // r4
    unsigned long cpu_size; // r5
    unsigned long gpu_size; // r6
}
void game_state_free_buffer(); // 0x837A7DA0
void game_state_create_or_open_file(); // 0x837A7DB0
void game_state_close_file()// 0x837A7DB8
{
$M19967:
}
unsigned char game_state_write_to_file(unsigned char do_autosave)// 0x837A7DF8
{
    unsigned char do_autosave; // r4
}
unsigned char hcex_game_state_read_from_file(void * data, int32_t data_size)// 0x837A7E10
{
    void * data; // r4
    int32_t data_size; // r5
}
unsigned char game_state_read_from_file(); // 0x837A7E28
unsigned char game_state_write_core(const char * name, void * buffer, long buffer_size)// 0x837A7E40
{
$M19981:
    const char * name; // r4
    void * buffer; // r5
    long buffer_size; // r6
    char filename[1024]; // r2 offset 96
    long bytes_written; // r2 offset 80
}
unsigned char game_state_read_core_header(const char * name, void * header, long header_size)// 0x837A7EF8
{
$M19989:
    const char * name; // r4
    void * header; // r5
    long header_size; // r6
    char filename[1024]; // r2 offset 96
    long bytes_read; // r2 offset 80
}
void game_state_read_core(const char * name, void * buffer, long buffer_size)// 0x837A7FA0
{
$M19995:
    const char * name; // r4
    void * buffer; // r5
    long buffer_size; // r6
    char filename[1024]; // r2 offset 96
    long bytes_read; // r2 offset 80
}
unsigned char game_state_read_header_from_persistent_storage(void * header, unsigned long * header_checksum, long header_size, long buffer_size, unsigned char * corrupted)// 0x837A82A0
{
$M20083:
    void * header; // r4
    unsigned long * header_checksum; // r5
    long header_size; // r6
    long buffer_size; // r7
    unsigned char * corrupted; // r8
    long bytes_read; // r2 offset 84
    unsigned long checksum; // r2 offset 80
    unsigned char checksum_buffer[131072]; // r2 offset 352
}
void game_state_write_to_persistent_storage(void * buffer, unsigned long * header_checksum, long header_size, long buffer_size)// 0x837A8450
{
$M20105:
    void * buffer; // r4
    unsigned long * header_checksum; // r5
    long header_size; // r6
    long buffer_size; // r7
    unsigned char saved_header[2048]; // r2 offset 352
    long bytes_written; // r2 offset 80
    unsigned long checksum; // r2 offset 84
}
void game_state_read_from_persistent_storage(void * buffer, long buffer_size)// 0x837A85A8
{
$M20126:
    void * buffer; // r4
    long buffer_size; // r5
    long bytes_read; // r2 offset 80
}
const char * game_state_get_persistent_storage_filename(); // 0x837A8028
void game_state_create_persistent_storage(const char * path)// 0x837A8650
{
$M20132:
    const char * path; // r4
}
unsigned char game_state_get_persistent_storage_path(char * path)// 0x837A8038
{
$M20003:
    char * path; // r4
}
void delete_persistent_storage()// 0x837A8070
{
$M20015:
    char path[256]; // r2 offset 80
}
void * game_state_open_persistent_storage(const char * directory)// 0x837A80B8
{
$M20054:
    const char * directory; // r4
    char path[256]; // r2 offset 96
    unsigned char empty_header[16384]; // r2 offset 608
    long bytes_written; // r2 offset 80
}