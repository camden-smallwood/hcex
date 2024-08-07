#include "cseries/cseries.h"
#include "input/input.h"
#include "shell/shell.h"

/* ---------- TODO: sort this stuff into appropriate files */

const short virtual_to_key_table[256];
const short ascii_to_key_table[128];
input_globals_xbox input_globals;

char faked_xbox_command_line[8];

void player_profile_load_builtin_profiles(const char *matched_name);

bool input_initialize(void);
void input_flush(void);
void input_activate(void);
void input_deactivate(void);
void input_update(void);
void input_set_gamepad_vibrate_state(short gamepad_index, unsigned short left_speed, unsigned short right_speed);
void input_vertical_blank_interrupt(void);
void input_frame_end(void);
void update_ticks(unsigned char *ticks, unsigned char down);
float apply_dead_zone_and_rescale(float value, float dead_range);
void apply_dead_zones(point2d *stick);
void input_frame_begin(void);
void input_update_keyboard(void)
{
    unsigned long dwUserIndex;   // r2 offset 84
    _XINPUT_KEYSTROKE keystroke; // r2 offset 88
    struct key_stroke key;              // r2 offset 80

#error TODO
}
bool input_key_is_down(short key_code);
const struct gamepad_state *input_get_gamepad_state(short gamepad_index);
void input_get_raw_data_string(char *buffer, short size);
bool input_has_gamepad(short gamepad_index);
bool input_get_key(struct key_stroke *key);
void input_key_debounce_update(void);

void server_info_message_to_player(int32_t player_index, int32_t strings_dll_message_id);

void hud_chat_initialize(void);
void hud_chat_dispose(void);
void hud_chat_close(void);
void hud_chat_box_clear(void);
unsigned char hud_chat_update(void);
void hud_chat_box_add_message(const wchar_t *message)
{
    const wchar_t *message; // r4
}

void controls_screen_cancel_config_mode(void);

/* ---------- public code */

bool shell_running_import_tool(void);
bool shell_application_is_paused(void);
void shell_screen_pause(bool paused);

bool shell_platform_initialize(void);
void shell_platform_dispose(void);
void shell_platform_verify(void);

bool shell_initialize(void);
void shell_dispose(void);
void shell_idle(void);

char *shell_get_command_line(void);
bool shell_get_clipboard_text(char *buffer, size_t length);
