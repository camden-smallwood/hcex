#include "cseries/cseries.h"
#include "bungie_net/common/thread.h"
#include "input/input_abstraction.h"
#include "tag_files/files.h"
#include "saved games/player_profile.h"

/* ---------- private structures */

struct player_profile_write_internal_input
{
    int32_t index;
    struct player_profile profile;
};

struct player_profile_internal
{
    struct player_profile profile;
    uint8_t checksum[4];
};

union player_profile_block
{
    uint8_t data[512];
    struct player_profile_internal profile_block;
};

/* ---------- private variables */

struct _player_profile_globals
{
    struct player_profile default_profile;
    struct player_profile_write_internal_input thread_input;
    struct thread *thread;
    bool initialized;
} player_profile_globals;

long profile_color_table[18];

/* ---------- public code */

void player_profiles_initialize(
    void);

void player_profiles_dispose(
    void);

void player_profiles_enumerate_available_to_local_player_index(
    short local_player_index,
    unsigned short *number_of_profiles,
    long *player_profile_indices,
    unsigned char include_default_profiles);

long player_profile_new(
    short local_player_index,
    unsigned short *name)
{
    struct file_reference profile_file; // r2 offset 80
    union player_profile_block block;   // r2 offset 352
}

void player_profile_delete(
    long player_profile_index);

unsigned char player_profile_get(
    long player_profile_index,
    struct player_profile *profile);

unsigned char player_profile_get_from_path(
    char *full_path,
    struct player_profile *profile)
{
    union player_profile_block block;   // r2 offset 368
    struct file_reference profile_file; // r2 offset 96
    unsigned char checksum[4];          // r2 offset 80
}

void player_profile_save(
    long player_profile_index,
    struct player_profile *profile);

real_argb_color player_profile_get_argb_color(
    long index);

unsigned short player_profile_number_of_available_primary_colors(
    void);

real_rgb_color player_profile_get_rgb_color(
    long index);

long player_profile_get_random_good_color(
    void);

long player_profile_get_random_color(
    void);

void player_profile_save_last_level_played(
    short local_player_index)
{
    struct player_profile profile; // r2 offset 80
}

void player_profile_save_level_completed(
    short local_player_index)
{
    struct player_profile profile; // r2 offset 80
}

void player_profile_get_highest_completed_solo_level(
    struct player_profile *profile,
    short *level,
    short *difficulty);

unsigned char player_profile_get_enclosing_directory_path(
    long player_profile_index,
    char *full_path);

void player_profile_setup_keyboard_default_bindings(
    struct player_profile *profile);

void player_profile_setup_mouse_default_bindings(
    struct player_profile *profile);

void player_profile_setup_default_gamespy_settings(
    struct player_profile *profile);

void player_profile_setup_default_server_settings(
    struct player_profile *profile);

void player_profile_build_default_profile(
    struct player_profile *profile,
    int32_t i,
    unsigned char try_inherit)
{
    struct player_profile inherit_profile; // r2 offset 96
    short number_of_custom_profiles;       // r2 offset 80
    long first_profile_index;              // r2 offset 84
}

void player_profile_create_default_profiles_on_disk(
    void)
{
    char full_path[256];              // r2 offset 2064
    union player_profile_block block; // r2 offset 80
    struct file_reference file;       // r2 offset 2320
}

unsigned char player_profile_read(
    long index,
    struct player_profile *profile)
{
    struct file_reference profile_file;      // r2 offset 96
    union player_profile_block block;        // r2 offset 2352
    unsigned char checksum[4];               // r2 offset 80
    struct player_profile sanitized_profile; // r2 offset 368
}

void do_write_profile_block(
    long index,
    struct player_profile *profile)
{
    struct file_reference profile_file; // r2 offset 80
    union player_profile_block block;   // r2 offset 352
}

unsigned char player_profile_write(
    long index,
    struct player_profile *profile);

unsigned char player_profile_find_button_for_binding(
    struct input_abstraction_input_button *button,
    const char *control_name);

void player_profile_unbind_button(
    struct input_abstraction_input_button *button);

unsigned char player_profile_bind_button_to_control(
    struct input_abstraction_input_button *button,
    short control);

unsigned char player_profile_load_default_mouse_settings(
    struct player_profile *profile);

unsigned char player_profile_load_default_video_settings(
    struct player_profile *profile,
    unsigned char try_inherit);

unsigned char player_profile_load_default_audio_settings(
    struct player_profile *profile,
    unsigned char try_inherit);
