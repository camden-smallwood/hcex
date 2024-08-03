#include "projects/code/hcex/sources/networking/message_delta_definitions.h"
#include "projects/code/hcex/sources/networking/message_delta_processor.h"
#include "projects/code/hcex/sources/networking/message_delta_messages.h"
#include "projects/code/hcex/sources/bungie_net/common/thread.h"
#include "projects/code/hcex/sources/saved games/playlist_profile.h"
#include "projects/code/hcex/sources/memory/sl_list.h"
#include "projects/code/hcex/sources/memory/texture_page.h"
#include "projects/code/hcex/sources/cseries/cseries.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/stdio.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/time.inl"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/pshpack4.h"
#include "projects/code/hcex/sources/saved games/player_profile.h"
#include "projects/code/hcex/sources/networking/network_game_globals.h"
#include "projects/code/hcex/sources/memory/bitstream.h"
#include "projects/code/hcex/sources/input/input_windows.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/poppack.h"
#include "projects/code/hcex/sources/interface/ui_gamespy_screen.h"
#include "projects/code/hcex/sources/interface/event_manager.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/basetsd.h"
#include "projects/code/hcex/sources/memory/circular_queue.h"
#include "projects/code/hcex/sources/math/integer_math.h"
#include "projects/code/hcex/sources/memory/lrar_cache.h"
#include "projects/code/hcex/sources/memory/hashtable.h"
#include "projects/code/hcex/sources/memory/byte_swapping.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/pshpack8.h"
#include "projects/code/hcex/sources/interface/ui_widget.h"
#include "projects/code/hcex/sources/interface/ui_widget_group.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/stdlib.h"
#include "projects/code/hcex/sources/xbox emulation/xbox_save_game.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/limits.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/winbase.h"
#include "projects/code/hcex/sources/saved games/game_state.h"
#include "projects/code/hcex/sources/memory/memory_pool.h"
#include "projects/code/hcex/sources/input/input.h"
#include "projects/code/hcex/sources/memory/data_packets.h"
#include "projects/code/hcex/sources/cseries/progress.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/guiddef.h"
#include "projects/code/hcex/sources/input/input_abstraction.h"
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
#include "projects/code/hcex/sources/saved games/saved_game_files.h"
#include "projects/code/hcex/sources/cache/cache_files.h"
#include "projects/code/hcex/sources/text/unicode.h"
#include "projects/code/hcex/sources/memory/lru_cache.h"
#include "projects/code/hcex/sources/main/code_timer.h"
#include "projects/code/hcex/sources/objects/index_resolution.h"
#include "projects/code/hcex/sources/cseries/errors.h"
#include "projects/code/hcex/sources/memory/data.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/winerror.h"
#include "projects/code/hcex/sources/bungie_net/common/message_header.h"
#include "projects/code/hcex/sources/math/geometry.h"
#include "projects/code/hcex/sources/bitmaps/bitmap_drawing.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/swprintf.inl"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/winnt.h"
#include "projects/code/hcex/sources/memory/lra_cache.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/ctype.h"
#include "projects/code/hcex/sources/game/game.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/malloc.h"
#include "projects/code/hcex/sources/game/cheats.h"
#include "projects/code/hcex/sources/memory/lruv_cache.h"
#include "projects/code/hcex/sources/halo_defines.h"
#include "projects/code/hcex/sources/cseries/headers.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/time.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/crtdefs.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/sal.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/codeanalysis/sourceannotations.h"
#include "projects/code/hcex/sources/math/periodic_functions.h"
#include "projects/code/hcex/sources/text/text_group.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/wtime.inl"
#include "projects/code/hcex/sources/game/game_engine.h"

char memory_unit_mapfile_name[255]; // 0x844CE230
_saved_game_files_globals saved_game_files_globals; // 0x844CE330
typedef _XGAME_FIND_DATA XGAME_FIND_DATA;
typedef _XGAME_FIND_DATA * PXGAME_FIND_DATA;
typedef long time_t;
void saved_game_files_initialize()// 0x837B45A8
{
$M19516:
}
void saved_game_files_dispose()// 0x837B4698
{
$M19522:
}
char * saved_game_files_get_path(short path_type)// 0x837B4708
{
    short path_type; // r4
}
void saved_game_files_enumerate_available_to_local_player_index(short player_index, unsigned short saved_game_file_type, unsigned short * number_of_profiles, long * player_profile_indices, unsigned char include_default_profiles)// 0x837B4728
{
    short player_index; // r4
    unsigned short saved_game_file_type; // r5
    unsigned short * number_of_profiles; // r6
    long * player_profile_indices; // r7
    unsigned char include_default_profiles; // r8
}
unsigned short * saved_game_file_get_display_name(long index)// 0x837B4738
{
    long index; // r4
    wchar_t display_name[128]; // data @ 0x844CE130
}
long create_enumerated_saved_game_file(unsigned short saved_game_file_type, short local_player_index, unsigned short * display_name)// 0x837B4750
{
    unsigned short saved_game_file_type; // r4
    short local_player_index; // r5
    unsigned short * display_name; // r6
}
unsigned char delete_enumerated_saved_game_file(long index)// 0x837B4758
{
$M19536:
    long index; // r4
}
unsigned char saved_game_file_open(file_reference * saved_game_file, long index)// 0x837B4780
{
    file_reference * saved_game_file; // r4
    long index; // r5
}
unsigned char saved_game_file_close(file_reference * saved_game_file, long index)// 0x837B4788
{
    file_reference * saved_game_file; // r4
    long index; // r5
}
unsigned short saved_game_file_get_type(long index)// 0x837B4790
{
    long index; // r4
}
void saved_game_files_delete_all_custom_profiles(); // 0x837B4798
void saved_game_files_notify_memory_units_changed(); // 0x837B47A0
void saved_game_file_get_useable_untitled_profile_name(unsigned short * display_name)// 0x837B47B8
{
    unsigned short * display_name; // r4
}
unsigned char delete_files_for_player_profile(const char * profile)// 0x837B47C8
{
$M19563:
    const char * profile; // r4
    char path[256]; // r2 offset 80
    char search_path[256]; // r2 offset 656
    _WIN32_FIND_DATAA find_data; // r2 offset 336
}
unsigned char copy_files_for_player_profile(const char * src_profile, const char * dst_profile)// 0x837B49C8
{
$M19580:
    const char * src_profile; // r4
    const char * dst_profile; // r5
    char new_path[256]; // r2 offset 336
    char old_path[256]; // r2 offset 80
    char search_path[256]; // r2 offset 912
    _WIN32_FIND_DATAA find_data; // r2 offset 592
}
unsigned char synchronize_metadata_display_name_with_profile_name(long index, unsigned short * game_display_name)// 0x837B4CB0
{
    long index; // r4
    unsigned short * game_display_name; // r5
}
unsigned char saved_game_files_take_mutex(); // 0x837B4CB8
void saved_game_files_release_mutex(); // 0x837B4CD0
unsigned char saved_game_file_get_path_to_enclosing_directory(long index, char * full_path)// 0x837B4CE0
{
    long index; // r4
    char * full_path; // r5
}
short saved_game_perform_file_system_checks(); // 0x837B4CF0
unsigned char saved_game_file_name_unique(unsigned short * name)// 0x837B4CF8
{
    unsigned short * name; // r4
}
void saved_game_file_remember_player1_last_used_profile_directory(char * directory_path)// 0x837B4D00
{
    char * directory_path; // r4
}
unsigned char saved_game_file_retrieve_player1_last_used_profile_directory(char * directory_path)// 0x837B4D08
{
    char * directory_path; // r4
}
void saved_game_file_remember_last_used_multiplayer_variant_directory(char * directory_path)// 0x837B4D10
{
    char * directory_path; // r4
}
unsigned char saved_game_file_retrieve_last_used_multiplayer_variant_directory(char * directory_path)// 0x837B4D18
{
    char * directory_path; // r4
}
long saved_game_file_find_profile_index_for_directory_path(char * directory_path, short saved_game_file_type)// 0x837B4D20
{
    char * directory_path; // r4
    short saved_game_file_type; // r5
}
void saved_game_file_remember_last_used_multiplayer_map(char * map_name)// 0x837B4D28
{
    char * map_name; // r4
}
unsigned char saved_game_file_retrieve_last_used_multiplayer_map(char * map_name)// 0x837B4D30
{
    char * map_name; // r4
}
void saved_game_file_generate_checksum(void * buffer, unsigned short buffer_size, unsigned char * checksum)// 0x837B4D38
{
$M19614:
    void * buffer; // r4
    unsigned short buffer_size; // r5
    unsigned char * checksum; // r6
}