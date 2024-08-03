#include "cseries/cseries.h"
#include "input/input_abstraction.h"

short _keyboard_auxbutton_mapping[3]; // 0x841ECFE0
_input_abstraction_globals input_abstraction_globals; // 0x844CDD98
const char control_to_name_table[16][21]; // 0x8211B0E0

void input_abstraction_update_debug(); // 0x837B2630
void input_abstraction_initialize()// 0x837B3280
{
$M29853:
}
void input_abstraction_dispose(); // 0x837B2638
void input_abstraction_reset_controller_detection_timer()// 0x837B2650
{
$M29647:
}
void input_abstraction_update()// 0x837B3E90
{
$M30075:
    unsigned long ignore_game_input_time; // data @ 0x844CDF74
}
void input_abstraction_flush(); // 0x837B2680
unsigned char input_abstraction_get_key(key_stroke * key)// 0x837B3308
{
    key_stroke * key; // r4
}
void input_abstraction_get_local_player_preferences(short local_player_index, game_input_preferences * preferences)// 0x837B26C8
{
    short local_player_index; // r4
    game_input_preferences * preferences; // r5
}
unsigned char input_abstraction_is_idle(); // 0x837B2708
void input_abstraction_update_local_player_preferences(short controller_index, game_input_preferences * preferences)// 0x837B2718
{
    short controller_index; // r4
    game_input_preferences * preferences; // r5
}
game_input_state * input_abstraction_get_input_state(short local_player_index)// 0x837B2758
{
    short local_player_index; // r4
}
void input_abstraction_update_device_changes(unsigned long device_change_flags)// 0x837B2780
{
$M29669:
    unsigned long device_change_flags; // r4
    unsigned long time_of_first_device_insertion; // data @ 0x844CDF78
}
short input_abstraction_get_current_mode(); // 0x837B2810
unsigned char input_abstraction_get_enabled_mode_game(); // 0x837B2870
unsigned char input_abstraction_get_enabled_mode_events(); // 0x837B2888
unsigned char input_abstraction_get_enabled_mode_keyboard(); // 0x837B28A0
unsigned char input_abstraction_get_enabled_mode_configuration(); // 0x837B28B8
void input_abstraction_set_enabled_mode_events(unsigned char enabled)// 0x837B28D0
{
    unsigned char enabled; // r4
}
void input_abstraction_set_enabled_mode_keyboard(unsigned char enabled)// 0x837B2908
{
    unsigned char enabled; // r4
}
void input_abstraction_set_enabled_mode_game(unsigned char enabled)// 0x837B2940
{
    unsigned char enabled; // r4
}
void input_abstraction_set_enabled_mode_configuration(unsigned char enabled)// 0x837B2958
{
$M29706:
    unsigned char enabled; // r4
}
unsigned char input_abstraction_auxbutton_down(short button)// 0x837B2A00
{
    short button; // r4
}
void input_abstraction_debounce_auxbutton_key(short key_code)// 0x837B2A18
{
    short key_code; // r4
}
unsigned char input_abstraction_is_action_button_down(short local_player_index, short button)// 0x837B2A70
{
    short local_player_index; // r4
    short button; // r5
}
void input_abstraction_get_configuration_button_pressed(input_abstraction_input_button * button)// 0x837B2AA0
{
    input_abstraction_input_button * button; // r4
}
unsigned char input_abstraction_has_configuration_button_pressed(); // 0x837B2AC8
void input_abstraction_flush_configuration_button_pressed(); // 0x837B2B50
void input_abstraction_test_config_one_control(char * control_specifier)// 0x837B2B70
{
    char * control_specifier; // r4
}
void input_abstraction_print_config_control(); // 0x837B2B78
void input_abstraction_bind(char * device_specifier, char * button_specifier, char * control_specifier)// 0x837B2B80
{
    char * device_specifier; // r4
    char * button_specifier; // r5
    char * control_specifier; // r6
}
void input_abstraction_unbind(char * device_specifier, char * button_specifier)// 0x837B2B88
{
    char * device_specifier; // r4
    char * button_specifier; // r5
}
void input_abstraction_print_binds(); // 0x837B2B90
void input_abstraction_get_name_for_button(input_abstraction_input_button * button, unsigned short * button_name)// 0x837B2B98
{
    input_abstraction_input_button * button; // r4
    unsigned short * button_name; // r5
}
void input_abstraction_set_yaw_rate(short local_player_index, float yaw_rate)// 0x837B2BA0
{
    short local_player_index; // r4
    float yaw_rate; // r43
}
void input_abstraction_set_pitch_rate(short local_player_index, float pitch_rate)// 0x837B2BC8
{
    short local_player_index; // r4
    float pitch_rate; // r43
}
float input_abstraction_get_yaw_rate(short local_player_index)// 0x837B2BF0
{
    short local_player_index; // r4
}
float input_abstraction_get_pitch_rate(short local_player_index)// 0x837B2C18
{
    short local_player_index; // r4
}
void input_mode_handle_game_xbox()// 0x837B3380
{
$M30043:
    game_input_state old_input; // r2 offset 240
    const float one_over_short_max; // data @ 0x8211B0C8
    const float reference_values[4]; // data @ 0x8211B0CC
    <unnamed-tag> PLAYER2; // constant == 1
    <unnamed-tag> PLAYER1; // constant == 0
    <unnamed-tag> PLAYER4; // constant == 3
    <unnamed-tag> PLAYER3; // constant == 2
}
void input_mode_handle_events()// 0x837B2C40
{
$M29790:
    unsigned long last_dpad_up[4]; // data @ 0x844CDF7C
    unsigned long last_dpad_right[4]; // data @ 0x844CDFAC
    unsigned long last_dpad_down[4]; // data @ 0x844CDF8C
    unsigned long last_dpad_left[4]; // data @ 0x844CDF9C
    long last_left_analog_stick_y[4]; // data @ 0x844CDFEC
    unsigned long left_analog_stick_timer[4]; // data @ 0x844CDFBC
    unsigned long right_analog_stick_timer[4]; // data @ 0x844CDFCC
    long last_right_analog_stick_y[4]; // data @ 0x844CE00C
    long last_left_analog_stick_x[4]; // data @ 0x844CDFDC
    long last_right_analog_stick_x[4]; // data @ 0x844CDFFC
}
void input_mode_handle_keyboard(); // 0x837B3008
void input_mode_handle_configuration(); // 0x837B3030
unsigned char input_abstraction_input_state_idle(const game_input_state * new_state, const game_input_state * old_state)// 0x837B3038
{
    const game_input_state * new_state; // r4
    const game_input_state * old_state; // r5
}
unsigned char local_player_is_piloting_aircraft(short controller_index)// 0x837B3130
{
$M29825:
    short controller_index; // r4
}
short input_abstraction_get_game_control_byname(const char * control_specifier)// 0x837B3220
{
$M29836:
    const char * control_specifier; // r4
}