#include "cseries/cseries.h"
#include "input/input_device_defaults.h"

#if defined(PLATFORM_WINDOWS)
#include <guiddef.h>
#else
#error unsupported platform
#endif

typedef GUID deviceid;
GUID input_device_defaults_keyboard_mouse_guid; // 0x8212DBEC

/* ---------- public code */

long input_device_defaults_find(GUID id, player_profile *profile)
{
    tag_iterator iterator; // r2 offset 80
}

void input_device_defaults_create_builtin_profiles(const wchar_t *name) // 0x83873980
{
    tag_iterator iterator;      // r2 offset 80
    player_profile new_profile; // r2 offset 112
}

/* ---------- private code */

static void test_input_device_defaults_find(const char *id_string)
{
    player_profile profile; // r2 offset 96
    GUID key;               // r2 offset 80
}

static unsigned char copy_relevant_profile_data(int32_t type, player_profile *dst, const player_profile *profile) // 0x83873890
{
}
