#include "projects/code/hcex/sources/game/game.h"
#include "projects/code/hcex/sources/game/cheats.h"
#include "projects/code/hcex/sources/networking/network_game_globals.h"
#include "projects/code/hcex/sources/bungie_net/common/message_header.h"
#include "projects/code/hcex/sources/memory/sl_list.h"
#include "projects/code/hcex/sources/memory/texture_page.h"
#include "projects/code/hcex/sources/cseries/cseries.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/stdio.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/time.inl"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/pshpack4.h"
#include "projects/code/hcex/sources/bungie_net/common/thread.h"
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
#include "projects/code/hcex/sources/game/game_engine.h"
#include "projects/code/hcex/sources/networking/message_delta_definitions.h"
#include "projects/code/hcex/sources/networking/message_delta_processor.h"
#include "projects/code/hcex/sources/saved games/saved_game_files.h"
#include "projects/code/hcex/sources/memory/data_packets.h"
#include "projects/code/hcex/sources/cseries/progress.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/guiddef.h"
#include "projects/code/hcex/sources/networking/message_delta_messages.h"
#include "projects/code/hcex/sources/input/input.h"
#include "projects/code/hcex/sources/input/input_windows.h"
#include "projects/code/hcex/sources/interface/ui_gamespy_screen.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/stddef.h"
#include "projects/code/hcex/sources/interface/event_manager.h"
#include "projects/code/hcex/sources/interface/ui_widget.h"
#include "projects/code/hcex/sources/memory/crc.h"
#include "projects/code/hcex/sources/interface/ui_widget_group.h"
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
#include "projects/code/hcex/sources/saved games/playlist_profile.h"
#include "projects/code/hcex/sources/cache/cache_files.h"
#include "projects/code/hcex/sources/text/unicode.h"
#include "projects/code/hcex/sources/memory/lru_cache.h"
#include "projects/code/hcex/sources/cseries/errors.h"
#include "projects/code/hcex/sources/main/code_timer.h"
#include "projects/code/hcex/sources/memory/data.h"
#include "projects/code/hcex/sources/objects/index_resolution.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/winerror.h"
#include "projects/code/hcex/sources/text/text_group.h"
#include "projects/code/hcex/sources/saved games/player_profile.h"
#include "projects/code/hcex/sources/input/input_abstraction.h"
#include "projects/code/hcex/sources/math/geometry.h"
#include "projects/code/hcex/sources/bitmaps/bitmap_drawing.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/swprintf.inl"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/winnt.h"
#include "projects/code/hcex/sources/memory/lra_cache.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/ctype.h"
#include "projects/code/hcex/sources/memory/bitstream.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/malloc.h"
#include "projects/code/hcex/sources/halo_defines.h"
#include "projects/code/hcex/sources/cseries/headers.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/time.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/crtdefs.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/sal.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/codeanalysis/sourceannotations.h"
#include "projects/code/hcex/sources/math/periodic_functions.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/wtime.inl"

game_variant(*default_variant_building_functions)()[38]; // 0x841F3710
_playlist_profile_globals playlist_profile_globals; // 0x844D94C0
typedef long time_t;
void playlist_profiles_initialize()// 0x8380CF58
{
$M18733:
}
void playlist_profiles_dispose()// 0x8380CFA0
{
$M18741:
}
void playlist_profiles_enumerate_available_to_local_player_index(short local_player_index, unsigned short * number_of_profiles, long * playlist_profile_indices)// 0x8380D6F0
{
$M18812:
    short local_player_index; // r4
    unsigned short * number_of_profiles; // r5
    long * playlist_profile_indices; // r6
    unsigned char first_time; // data @ 0x841F37A8
}
long playlist_profile_new(short local_player_index, unsigned short * name)// 0x8380D008
{
$M18752:
    short local_player_index; // r4
    unsigned short * name; // r5
    file_reference playlist_file; // r2 offset 752
    playlist_profile_block block; // r2 offset 240
    game_variant slayer; // r2 offset 80
}
void playlist_profile_delete(long playlist_profile_index)// 0x8380D130
{
    long playlist_profile_index; // r4
}
unsigned char playlist_profile_get(long playlist_profile_index, game_variant * variant)// 0x8380D748
{
$M18818:
    long playlist_profile_index; // r4
    game_variant * variant; // r5
}
unsigned char playlist_profile_get_from_path(char * full_path, game_variant * variant)// 0x8380D140
{
$M18764:
    char * full_path; // r4
    game_variant * variant; // r5
    playlist_profile_block block; // r2 offset 368
    file_reference profile_file; // r2 offset 96
    unsigned char checksum[4]; // r2 offset 80
}
unsigned char playlist_profile_get_display_name(long playlist_profile_index, unsigned short * display_name)// 0x8380D228
{
$M18770:
    long playlist_profile_index; // r4
    unsigned short * display_name; // r5
}
void playlist_profile_save(long playlist_profile_index, game_variant * variant)// 0x8380D818
{
$M18841:
    long playlist_profile_index; // r4
    game_variant * variant; // r5
}
unsigned short playlist_profile_number_of_default_profiles_on_disk(); // 0x8380D290
void playlist_profile_create_default_profiles_on_disk()// 0x8380D2A0
{
$M18783:
    char full_path[256]; // r2 offset 80
    playlist_profile_block block; // r2 offset 608
    game_variant game_variant; // r2 offset 1120
    file_reference file; // r2 offset 336
}
unsigned char playlist_profile_read(long index, game_variant * variant)// 0x8380D460
{
$M18799:
    long index; // r4
    game_variant * variant; // r5
    file_reference playlist_file; // r2 offset 416
    playlist_profile_block block; // r2 offset 688
    unsigned char checksum[4]; // r2 offset 80
    game_variant sanitized_variant; // r2 offset 96
    game_variant sanitized_variant; // r2 offset 96
}
unsigned char playlist_profile_write(long index, game_variant * variant)// 0x8380D798
{
$M18826:
    long index; // r4
    game_variant * variant; // r5
}
unsigned long playlist_profile_write_thread_proc(void * input)// 0x8380D608
{
$M18806:
    void * input; // r4
    file_reference playlist_file; // r2 offset 80
    playlist_profile_block block; // r2 offset 352
}