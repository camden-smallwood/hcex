#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

/* ---------- macros */

#ifndef __has_builtin
#   error unsupported compiler, __has_builtin not defined
#endif

#if __has_builtin(__builtin_clz)
#   define COUNT_BITS(bits) ((sizeof(int) * 8) - __builtin_clz(bits))
#else
#   error __builtin_clz not defined
#endif

#if __has_builtin(__builtin_clzl)
#   define COUNT_BITS_LONG(bits) ((sizeof(long) * 8) - __builtin_clzl(bits))
#else
#   error __builtin_clzl not defined
#endif

#if __has_builtin(__builtin_clzll)
#   define COUNT_BITS_LONG_LONG(bits) ((sizeof(long long) * 8) - __builtin_clzll(bits))
#else
#   error __builtin_clzll not defined
#endif

#ifdef DEBUG
#   define assert(x) if (!(x)) display_assert(#x, __FILE__, __LINE__, true)
#else
#   define assert(x)
#endif

#define UNUSED(x) ((void)(x))

#define COUNT_OF(xs) (sizeof(xs) / sizeof((xs)[0]))

#define FLAG(bit_index) (1u << (bit_index))
#define TEST_FLAG(bits, bit_index) (((bits) & FLAG(bit_index)) != 0)
#define VALID_FLAGS(bits, bit_count) (((bits) ^ (FLAG(bit_count) - 1)) == 0)
#define SET_FLAG(bits, bit_index, value) ((bits) = ((value) ? ((bits) | FLAG(bit_index)) : ((bits) & ~FLAG(bit_index))))

/* ---------- types */

typedef uint32_t tag;

typedef float real;

/* ---------- constants */

enum
{
    NONE = -1,
};

enum
{
    _x,
    _y,
    _z,

    NUMBER_OF_RECTANGLE2D_COMPONENTS = 4,
    NUMBER_OF_RECTANGLE3D_COMPONENTS = 6,
    NUMBER_OF_VERTICES_PER_LINE = 2,
    NUMBER_OF_VERTICES_PER_TRIANGLE = 3,
    NUMBER_OF_VERTICES_PER_QUADRALATERAL = 4,
    NUMBER_OF_VERTICES_PER_QUADRILATERAL = 4,
    NUMBER_OF_VERTICES_PER_HEXAGON = 6,
    NUMBER_OF_VERTICES_PER_PYRAMID = 5,
    NUMBER_OF_VERTICES_PER_CUBE = 8,
    NUMBER_OF_TRIANGLES_PER_QUADRILATERAL = 2,
    NUMBER_OF_EDGES_PER_TRIANGLE = 3,
    NUMBER_OF_EDGES_PER_QUADRALATERAL = 4,
    NUMBER_OF_EDGES_PER_HEXAGON = 6,
    NUMBER_OF_FACES_PER_CUBE = 6,

    /* points per rectangle */
    _rectangle_top_left = 0,
    _rectangle_bottom_left,
    _rectangle_top_right,
    _rectangle_bottom_right,
    NUMBER_OF_POINTS_PER_RECTANGLE
};

//
// NOTE:
//   We shouldn't use these.
//   We should use the values defined in <limits.h>
//
// enum
// {
//     UNSIGNED_LONG_MAX = 4294967295,
//     LONG_MAX = 2147483647L,
//     LONG_MIN = (-2147483648L),
//     LONG_BITS = 32,
//     LONG_BITS_BITS = COUNT_BITS(LONG_BITS),
//
//     UNSIGNED_SHORT_MAX = 65535,
//     SHORT_MAX = 32767,
//     SHORT_MIN = (-32768),
//     SHORT_BITS = 16,
//     SHORT_BITS_BITS = COUNT_BITS(SHORT_BITS),
//
//     UNSIGNED_CHAR_MAX = 255,
//     CHAR_MAX = 127,
//     CHAR_MIN = (-128),
//     CHAR_BITS = 8,
//     CHAR_BITS_BITS = COUNT_BITS(CHAR_BITS),
// };

/* ---------- math types */

typedef union byte_rectangle3d
{
    uint8_t n[6];
    struct
    {
        uint8_t x0;
        uint8_t x1;
        uint8_t y0;
        uint8_t y1;
        uint8_t z0;
        uint8_t z1;
    };
} byte_rectangle3d;

typedef union point2d
{
    int16_t n[2];
    struct
    {
        int16_t x;
        int16_t y;
    };
} point2d;

typedef union point3d
{
    int16_t n[3];
    struct
    {
        int16_t x;
        int16_t y;
        int16_t z;
    };
} point3d;

typedef union point4d
{
    int16_t n[4];
    struct
    {
        int16_t x;
        int16_t y;
        int16_t z;
        int16_t w;
    };
} point4d;

typedef union rectangle2d
{
    int16_t n[4];
    int16_t m[2][2];
    struct
    {
        int16_t y0;
        int16_t x0;
        int16_t y1;
        int16_t x1;
    };
} rectangle2d;

typedef union rgb_color
{
    uint16_t n[3];
    struct
    {
        uint16_t red;
        uint16_t green;
        uint16_t blue;
    };
} rgb_color;

typedef union argb_color
{
    uint16_t n[4];
    struct
    {
        uint16_t alpha;
        union
        {
            rgb_color rgb;
            struct
            {
                uint16_t red;
                uint16_t green;
                uint16_t blue;
            };
        };
    };
} argb_color;

typedef union hsv_color
{
    uint16_t n[3];
    struct
    {
        uint16_t hue;
        uint16_t saturation;
        uint16_t value;
    };
} hsv_color;

typedef union real_rgb_color
{
    real n[3];
    struct
    {
        real red;
        real green;
        real blue;
    };
} real_rgb_color;

typedef union real_argb_color
{
    real n[4];
    struct
    {
        real alpha;
        union
        {
            real_rgb_color rgb;
            struct
            {
                real red;
                real green;
                real blue;
            };
        };
    };
} real_argb_color;

typedef union real_hsv_color
{
    real n[3];
    struct
    {
        real hue;
        real saturation;
        real value;
    };
} real_hsv_color;

typedef union real_point2d
{
    real n[2];
    struct
    {
        real x;
        real y;
    };
    struct
    {
        real u;
        real v;
    };
} real_point2d;

typedef union real_point3d
{
    real n[3];
    struct
    {
        real x;
        real y;
        real z;
    };
    struct
    {
        real u;
        real v;
        real w;
    };
} real_point3d;

typedef union real_vector2d
{
    real n[2];
    struct
    {
        real i;
        real j;
    };
} real_vector2d;

typedef union real_vector3d
{
    real n[3];
    struct
    {
        real i;
        real j;
        real k;
    };
} real_vector3d;

typedef union real_vector4d
{
    real n[4];
    struct
    {
        real i;
        real j;
        real k;
        real l;
    };
} real_vector4d;

typedef struct real_plane2d
{
    real_vector2d n;
    real d;
} real_plane2d;

typedef struct real_plane3d
{
    real_vector3d n;
    real d;
} real_plane3d;

typedef union real_rectangle2d
{
    real n[4];
    real m[2][2];
    struct
    {
        real x0;
        real x1;
        real y0;
        real y1;
    };
} real_rectangle2d;

typedef union real_rectangle3d
{
    real n[6];
    real m[2][3];
    struct
    {
        real x0;
        real x1;
        real y0;
        real y1;
        real z0;
        real z1;
    };
} real_rectangle3d;

typedef struct real_quaternion
{
    real_vector3d v;
    real w;
} real_quaternion;

typedef struct real_orientation
{
    real_quaternion rotation;
    real_point3d translation;
    real scale;
} real_orientation;

typedef union real_euler_angles2d
{
    real n[2];
    struct
    {
        real yaw;
        real pitch;
    };
} real_euler_angles2d;

typedef union real_euler_angles3d
{
    real n[3];
    struct
    {
        real yaw;
        real pitch;
        real roll;
    };
} real_euler_angles3d;

typedef struct real_matrix3x3
{
    union
    {
        real n[3][3];
        real_vector3d basis[3];
        real_vector3d forward;
    };
    real_vector3d left;
    real_vector3d up;
} real_matrix3x3;

typedef struct real_matrix4x3
{
    real scale;
    union
    {
        struct
        {
            union
            {
                real n[3][4];
                real_matrix3x3 matrix3x3;
                real_vector3d basis[3];
            };
            real_point3d origin;
        };
        struct
        {
            real_vector3d forward;
            real_vector3d left;
            real_vector3d up;
            real_point3d position;
        };
    };
} real_matrix4x3;

/* ---------- global colors */

extern const real_argb_color *global_real_argb_white;
extern const real_argb_color *global_real_argb_grey;
extern const real_argb_color *global_real_argb_black;
extern const real_argb_color *global_real_argb_red;
extern const real_argb_color *global_real_argb_green;
extern const real_argb_color *global_real_argb_blue;
extern const real_argb_color *global_real_argb_cyan;
extern const real_argb_color *global_real_argb_yellow;
extern const real_argb_color *global_real_argb_magenta;
extern const real_argb_color *global_real_argb_pink;
extern const real_argb_color *global_real_argb_lightblue;
extern const real_argb_color *global_real_argb_orange;
extern const real_argb_color *global_real_argb_purple;
extern const real_argb_color *global_real_argb_aqua;
extern const real_argb_color *global_real_argb_darkgreen;
extern const real_argb_color *global_real_argb_salmon;
extern const real_argb_color *global_real_argb_violet;

extern const real_rgb_color *global_real_rgb_white;
extern const real_rgb_color *global_real_rgb_grey;
extern const real_rgb_color *global_real_rgb_black;
extern const real_rgb_color *global_real_rgb_red;
extern const real_rgb_color *global_real_rgb_green;
extern const real_rgb_color *global_real_rgb_blue;
extern const real_rgb_color *global_real_rgb_cyan;
extern const real_rgb_color *global_real_rgb_yellow;
extern const real_rgb_color *global_real_rgb_magenta;
extern const real_rgb_color *global_real_rgb_pink;
extern const real_rgb_color *global_real_rgb_lightblue;
extern const real_rgb_color *global_real_rgb_orange;
extern const real_rgb_color *global_real_rgb_purple;
extern const real_rgb_color *global_real_rgb_aqua;
extern const real_rgb_color *global_real_rgb_darkgreen;
extern const real_rgb_color *global_real_rgb_salmon;
extern const real_rgb_color *global_real_rgb_violet;

/* ---------- inline code */

static inline long fast_ftol(real d)
{
    return (long)d;
}

// TODO: is there a difference????
static inline long fast_ftol_C(real d)
{
    return (long)d;
}

/* ---------- prototypes/CSERIES.C */

void cseries_initialize(void);
void cseries_dispose(void);

tag string_to_tag(const char *s);
char *tag_to_string(tag t, char *s);

int strnicmp(const char *string1, const char *string2, size_t count);
char *stristr(const char *haystack, const char *needle);
char *strnupr(char *string, int n);
char *strnlwr(char *string, int n);
char *strupr(char *string);
char *strlwr(char *string);

uint32_t string_hash(const char *string);

char *csprintf(char *buffer, char *format, ...);
int csstrcasecmp(const char *s1, const char *s2);

void display_assert(char *information, char *file, int line, bool fatal);

/* ---------- prototypes/SORT.C */

typedef int(*compare_function_2byte)(uint16_t, uint16_t);
void qsort_2byte(void *base, size_t num, compare_function_2byte compare);

typedef int(*compare_function_4byte)(uint32_t, uint32_t);
void qsort_4byte(void *base, size_t num, compare_function_4byte compare);
