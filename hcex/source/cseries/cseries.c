#include <ctype.h>
#include <wctype.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "cseries/cseries.h"
#include "cseries/cseries_windows.h"
#include "cseries/errors.h"
#include "memory/crc.h"

/* ---------- global colors */

static const real_argb_color private_real_argb_colors[] =
{
    { 1.0, 1.0, 1.0, 1.0 },
    { 1.0, 0.5, 0.5, 0.5 },
    { 1.0, 0.0, 0.0, 0.0 },
    { 1.0, 1.0, 0.0, 0.0 },
    { 1.0, 0.0, 1.0, 0.0 },
    { 1.0, 0.0, 0.0, 1.0 },
    { 1.0, 0.0, 1.0, 1.0 },
    { 1.0, 1.0, 1.0, 0.0 },
    { 1.0, 1.0, 0.0, 1.0 },
    { 1.0, 1.0, 0.41, 0.69999999 },
    { 1.0, 0.38999999, 0.57999998, 0.93000001 },
    { 1.0, 1.0, 0.5, 0.0 },
    { 1.0, 0.44, 0.050000001, 0.43000001 },
    { 1.0, 0.5, 1.0, 0.82999998 },
    { 1.0, 0.0, 0.38999999, 0.0 },
    { 1.0, 1.0, 0.63, 0.47999999 },
    { 1.0, 0.81, 0.13, 0.56 },
};

const real_argb_color *global_real_argb_white = &private_real_argb_colors[0];
const real_argb_color *global_real_argb_grey = &private_real_argb_colors[1];
const real_argb_color *global_real_argb_black = &private_real_argb_colors[2];
const real_argb_color *global_real_argb_red = &private_real_argb_colors[3];
const real_argb_color *global_real_argb_green = &private_real_argb_colors[4];
const real_argb_color *global_real_argb_blue = &private_real_argb_colors[5];
const real_argb_color *global_real_argb_cyan = &private_real_argb_colors[6];
const real_argb_color *global_real_argb_yellow = &private_real_argb_colors[7];
const real_argb_color *global_real_argb_magenta = &private_real_argb_colors[8];
const real_argb_color *global_real_argb_pink = &private_real_argb_colors[9];
const real_argb_color *global_real_argb_lightblue = &private_real_argb_colors[10];
const real_argb_color *global_real_argb_orange = &private_real_argb_colors[11];
const real_argb_color *global_real_argb_purple = &private_real_argb_colors[12];
const real_argb_color *global_real_argb_aqua = &private_real_argb_colors[13];
const real_argb_color *global_real_argb_darkgreen = &private_real_argb_colors[14];
const real_argb_color *global_real_argb_salmon = &private_real_argb_colors[15];
const real_argb_color *global_real_argb_violet = &private_real_argb_colors[16];

const real_rgb_color *global_real_rgb_white = &private_real_argb_colors[0].rgb;
const real_rgb_color *global_real_rgb_grey = &private_real_argb_colors[1].rgb;
const real_rgb_color *global_real_rgb_black = &private_real_argb_colors[2].rgb;
const real_rgb_color *global_real_rgb_red = &private_real_argb_colors[3].rgb;
const real_rgb_color *global_real_rgb_green = &private_real_argb_colors[4].rgb;
const real_rgb_color *global_real_rgb_blue = &private_real_argb_colors[5].rgb;
const real_rgb_color *global_real_rgb_cyan = &private_real_argb_colors[6].rgb;
const real_rgb_color *global_real_rgb_yellow = &private_real_argb_colors[7].rgb;
const real_rgb_color *global_real_rgb_magenta = &private_real_argb_colors[8].rgb;
const real_rgb_color *global_real_rgb_pink = &private_real_argb_colors[9].rgb;
const real_rgb_color *global_real_rgb_lightblue = &private_real_argb_colors[10].rgb;
const real_rgb_color *global_real_rgb_orange = &private_real_argb_colors[11].rgb;
const real_rgb_color *global_real_rgb_purple = &private_real_argb_colors[12].rgb;
const real_rgb_color *global_real_rgb_aqua = &private_real_argb_colors[13].rgb;
const real_rgb_color *global_real_rgb_darkgreen = &private_real_argb_colors[14].rgb;
const real_rgb_color *global_real_rgb_salmon = &private_real_argb_colors[15].rgb;
const real_rgb_color *global_real_rgb_violet = &private_real_argb_colors[16].rgb;

/* ---------- public variables */

char temporary[256];

/* ---------- public code */

void cseries_initialize(
    void)
{
#   warning TODO: reference other platform implementations

    cseries_platform_initialize();
}

void cseries_dispose(
    void)
{
#   warning TODO: reference other platform implementations
}

tag string_to_tag(
    const char *s)
{
    return s[0] | (s[1] << 8) | (s[2] << 16) | (s[3] << 24);
}

char *tag_to_string(
    tag t,
    char *s)
{
    s[0] = (t >> 0) & 0xFF;
    s[1] = (t >> 8) & 0xFF;
    s[2] = (t >> 16) & 0xFF;
    s[3] = (t >> 24) & 0xFF;
    s[4] = 0;

    return s;
}

int strnicmp(
    const char *string1,
    const char *string2,
    size_t count)
{
    if (count == 0)
    {
        return 0;
    }
    
    const char *v3 = string1 - 1;
    const char *v4 = string2 - 1;

    int v5, v6;

    do
    {
        v5 = *++v3;
        
        if (v5 >= 'A' && *v3 <= 'Z')
        {
            v5 += 32;
        }
        
        v6 = *++v4;
        
        if (v6 >= 'A' && *v4 <= 'Z')
        {
            v6 += 32;
        }
        
        --count;
    }
    while (count && v5 && v5 == v6);

    return v5 - v6;
}

char *stristr(
    const char *haystack,
    const char *needle)
{
    const char *v3 = needle + 1;
    char v4 = *needle;

    if (*needle)
    {
        const char *v5 = needle + 1;
        while (*v5++);

        int v7 = v5 - v3 - 1;
        
        while (true)
        {
            char v8 = *haystack++;

            if (!v8)
            {
                return NULL;
            }
            
            if (v8 == v4 && !strnicmp(haystack, v3, v7))
            {
                --haystack;
                return (char *)haystack;
            }
        }
        
        return NULL;
    }
    
    return (char *)haystack;
}

char *strnupr(
    char *string,
    int n)
{
    for (char *i = string; *i; ++i)
    {
        if (n-- <= 0)
        {
            break;
        }
        
        *i = toupper(*i);
    }

    return string;
}

char *strnlwr(
    char *string,
    int n)
{
    for (char *i = string; *i; ++i)
    {
        if (n-- <= 0)
        {
            break;
        }

        *i = tolower(*i);
    }

    return string;
}

char *strupr(
    char *string)
{
    for (char *i = string; *i; ++i)
    {
        *i = toupper(*i);
    }

    return string;
}

char *strlwr(
    char *string)
{
    char *v1 = string;

    for (char *i = string; *i; ++i)
    {
        *i = tolower(*i);
    }

    return v1;
}

uint32_t string_hash(
    const char *string)
{
    uint32_t v5[4];
    crc_new(v5);

    const char *v2 = string;
    while (*v2++);

    crc_checksum_buffer(v5, string, v2 - string - 1);

    return v5[0];
}

char *csprintf(
    char *buffer,
    char *format,
    ...)
{
    va_list va;
    va_start(va, format);

    vsprintf(buffer, format, va);
    
    va_end(va);
    
    return buffer;
}

int csstrcasecmp(
    const char *s1,
    const char *s2)
{
    wint_t v4 = towlower(*s1);
    wint_t v5 = towlower(*s2);

    if (v4 == 0)
    {
        return (v5 == 0) - 1;
    }

    wint_t v6 = s1 - s2;

    while (true)
    {
        if (v5 == 0)
        {
            return v4 != 0;
        }

        if (v4 != v5)
        {
            break;
        }
        
        ++s2;

        v4 = towlower(s2[v6]);
        v5 = towlower(*s2);

        if (v4 == 0)
        {
            return (v5 == 0) - 1;
        }
    }
    
    if (v4 <= v5)
    {
        return -1;
    }
    
    return 1;
}

void display_assert(
    char *information,
    char *file,
    int line,
    bool fatal)
{
#ifndef DEBUG
    UNUSED(information);
    UNUSED(file);
    UNUSED(line);
    UNUSED(fatal);
#else
    if (fatal)
        stack_walk(0);
    
    error(
        _error_message_priority_assert,
        "EXCEPTION %s in %s,#%d: %s",
        fatal ? "halt" : "warn",
        file,
        line,
        information ? information : "<no reason given>");
#endif
}
