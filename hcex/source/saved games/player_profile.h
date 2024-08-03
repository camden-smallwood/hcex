#pragma once

/* ---------- structures */

struct player_profile
{
    uint8_t profile_version;
    wchar_t player_name[12];
    uint8_t player_name_reserved[256];
    int16_t primary_color_index;
    uint16_t flags;
    int8_t single_player_map_flags[10];
    int16_t last_single_player_map_played;

    struct _controller_settings
    {
        bool button_preset;
        bool joystick_preset;
        bool look_sensitivity;
        bool invert_look;
        bool vibration_disabled;
        bool flight_stick_aircraft_controls;
        bool autocenter;
        bool ingame_help_disabled;

        #warning TODO: use constant for array length
        uint8_t game_control_to_xbox_buttons[21];
    } controller_settings;

    uint8_t reserved[1652];
};

/* ---------- prototypes/PLAYER_PROFILE.C */

#warning TODO
