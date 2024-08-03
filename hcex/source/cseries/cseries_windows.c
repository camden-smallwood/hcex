#include "cseries/cseries.h"
#include "cseries/cseries_windows.h"

#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#   include <winbase.h>
#   include <winnt.h>
#   include <profileapi.h>
#   include <errhandlingapi.h>
#elif defined(__APPLE__) && defined(__MACH__)
#   include <errno.h>
#   include <mach/mach_time.h>
#else
#   error unsupported platform
#endif

/* ---------- public constants */

const struct system_unique_identifier system_unique_identifier_zero = {
    .data = {0},
};

/* ---------- private variables */

#ifdef _WIN32
    LARGE_INTEGER s_ClockFrequency;
#elif defined(__APPLE__) && defined(__MACH__)
    mach_timebase_info_data_t g_timebase_info;
#endif

char scratch_disk_root[261];

/* ---------- private prototypes */

#ifdef _WIN32
static char *exception_code_get_string(unsigned int exception_code);
static int generic_exception_filter(unsigned int exception_code, EXCEPTION_POINTERS *exception_information);
#endif

static void initialize_scratch_disk_root(void);

/* ---------- public code */

void cseries_platform_initialize(
    void)
{
    system_timer_init();
    initialize_scratch_disk_root();
}

void system_exit(
    int code)
{
    exit(code);
}

uint32_t system_get_error_code(
    void)
{
#if defined(PLATFORM_WINDOWS)
    return (uint32_t)GetLastError();
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
    return (uint32_t)errno;
#else
#   error unsupported platform
#endif
}

void system_set_error_code(
    uint32_t error_code)
{
#if defined(PLATFORM_WINDOWS)
    SetLastError((DWORD)error_code);
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
    errno = (int)error_code;
#else
#   error unsupported platform
#endif
}

void system_unique_identifier_get(
    struct system_unique_identifier *identifier)
{
#   warning TODO: reference other platform implementations

    UNUSED(identifier);
}

bool system_unique_identifiers_equal(
    const struct system_unique_identifier *identifier1,
    const struct system_unique_identifier *identifier2)
{
    return memcmp(identifier1, &system_unique_identifier_zero, sizeof(struct system_unique_identifier)) != 0
        && memcmp(identifier1, identifier2, sizeof(struct system_unique_identifier)) == 0;
}

void system_timer_init(
    void)
{
#ifdef _WIN32

    assert(QueryPerformanceFrequency(&s_ClockFrequency));

#elif defined(__APPLE__) && defined(__MACH__)

    mach_timebase_info(&g_timebase_info);
    
#else
#   error unsupported platform
#endif
}

uint32_t system_seconds(
    void)
{
#ifdef _WIN32

    if (s_ClockFrequency.QuadPart == 0)
        assert(QueryPerformanceFrequency(&s_ClockFrequency));

    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    return (uint32_t)(now.QuadPart / (double)s_ClockFrequency.QuadPart);

#elif defined(__APPLE__) && defined(__MACH__)
#   warning TODO: check if this is correct

    return (uint32_t)((mach_absolute_time() * (uint64_t)g_timebase_info.numer) / (double)g_timebase_info.denom);

#else
#   error unsupported platform
#endif
}

uint32_t system_milliseconds(
    void)
{
#ifdef _WIN32

    if (s_ClockFrequency.QuadPart == 0)
        assert(QueryPerformanceFrequency(&s_ClockFrequency));

    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    return (uint32_t)((now.QuadPart * 1000) / (double)s_ClockFrequency.QuadPart);

#elif defined(__APPLE__) && defined(__MACH__)
#   warning TODO: check if this is correct

    return (uint32_t)(1000 * ((mach_absolute_time() * (uint64_t)g_timebase_info.numer) / (double)g_timebase_info.denom));

#else
#   error unsupported platform
#endif
}

uint64_t system_microseconds(
    void)
{
#ifdef _WIN32

    if (s_ClockFrequency.QuadPart == 0)
        assert(QueryPerformanceFrequency(&s_ClockFrequency));

    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    return (uint64_t)((now.QuadPart * 1000000) / (double)s_ClockFrequency.QuadPart);

#elif defined(__APPLE__) && defined(__MACH__)
#   warning TODO: check if this is correct

    return (uint32_t)(1000000 * ((mach_absolute_time() * (uint64_t)g_timebase_info.numer) / (double)g_timebase_info.denom));

#else
#   error unsupported platform
#endif
}

int64_t system_clocks(
    void)
{
#ifdef _WIN32
#   warning TODO: check if this is correct

    if (s_ClockFrequency.LowPart == 0)
    {
        QueryPerformanceFrequency(&s_ClockFrequency);
    }

    LARGE_INTEGER v1;
    QueryPerformanceCounter(&v1);

    return v1.LowPart;

#elif defined(__APPLE__) && defined(__MACH__)
#   warning TODO

    return 0;

#else
#   error unsupported platform
#endif
}

uint32_t system_clocks_to_seconds(
    int64_t clocks)
{
#ifdef _WIN32
#   warning TODO: check if this is correct

    return clocks / s_ClockFrequency.QuadPart;

#elif defined(__APPLE__) && defined(__MACH__)
#   warning TODO

    return 0;

#else
#   error unsupported platform
#endif
}

uint32_t system_clocks_to_milliseconds(
    int64_t clocks)
{
#ifdef _WIN32
#   warning TODO

    return __SPAIR64__(
               ($D5D8D40E1589F99F79D006525E3FB385 *)&cache_file_globals_0.cached_map_files[0].header.unused2[449],
               s_ClockFrequency.HighPart) /
           s_ClockFrequency.QuadPart;

#elif defined(__APPLE__) && defined(__MACH__)
#   warning TODO

    return 0;

#else
#   error unsupported platform
#endif
}

uint64_t system_clocks_to_microseconds(
    int64_t clocks)
{
#ifdef _WIN32
#   warning TODO

    __int64 result; // r4 OVERLAPPED

    HIDWORD(a4) = 1000000;
    *(__int64 *)((char *)&result + 4) = (unsigned __int64)(*(_QWORD *)&retstr * *(__int64 *)((char *)&a4 + 4))
                                    / s_ClockFrequency.QuadPart;

    return result;

#elif defined(__APPLE__) && defined(__MACH__)
#   warning TODO

    return 0;

#else
#   error unsupported platform
#endif
}

double system_clock_delta_seconds_real(
    int64_t a,
    int64_t b)
{
#ifdef _WIN32
#   warning TODO

    __int64 v2; // r11

    LODWORD(v2) = HIDWORD(a) - a;
    HIDWORD(v2) = &cache_file_globals_0.cached_map_files[0].header.unused2[449];
    return (double)v2 / (double)s_ClockFrequency.QuadPart;

#elif defined(__APPLE__) && defined(__MACH__)
#   warning TODO

    return 0;

#else
#   error unsupported platform
#endif
}

uint32_t system_clock_delta_seconds(
    int64_t a,
    int64_t b)
{
#ifdef _WIN32
#   warning TODO

    return __SPAIR64__(
               ($D5D8D40E1589F99F79D006525E3FB385 *)&cache_file_globals_0.cached_map_files[0].header.unused2[449],
               s_ClockFrequency.HighPart) /
           s_ClockFrequency.QuadPart;

#elif defined(__APPLE__) && defined(__MACH__)
#   warning TODO

    return 0;

#else
#   error unsupported platform
#endif
}

uint32_t system_clock_delta_milliseconds(
    int64_t a,
    int64_t b)
{
#ifdef _WIN32
#   warning TODO

    LODWORD(a4) = 1000 * (HIDWORD(a) - a);
    return a4 / s_ClockFrequency.QuadPart;

#elif defined(__APPLE__) && defined(__MACH__)
#   warning TODO

    return 0;

#else
#   error unsupported platform
#endif
}

uint32_t system_clock_delta_microseconds(
    int64_t a,
    int64_t b)
{
#ifdef _WIN32
#   warning TODO

    int v2; // r7

    v2 = 1000000;
    return (__int64)(__PAIR64__(
                         ($D5D8D40E1589F99F79D006525E3FB385 *)&cache_file_globals_0.cached_map_files[0].header.unused2[449],
                         s_ClockFrequency.HighPart) *
                     *(__int64 *)((char *)&b - 4)) /
           s_ClockFrequency.QuadPart;

#elif defined(__APPLE__) && defined(__MACH__)
#   warning TODO

    return 0;

#else
#   error unsupported platform
#endif
}

size_t system_get_date_time_string(
    char *date_time_string,
    size_t max_length_in_bytes)
{
#ifdef _WIN32
#   warning TODO

    const tm *v4; // r3
    int v6[2];    // [sp+50h] [-20h] BYREF

    time32(v6);
    v4 = localtime32(v6);
    return strftime(date_time_string, max_length_in_bytes, "%Y-%m-%d %H_%M_%S", v4);

#elif defined(__APPLE__) && defined(__MACH__)
#   warning TODO

    return 0;

#else
#   error unsupported platform
#endif
}

void system_get_user_name(
    char *name,
    size_t maximum_length)
{
#   warning TODO: reference other platform implementations

    strncpy(name, "xbox", maximum_length);
}

char *system_get_scratch_disk_root(
    void)
{
    return scratch_disk_root;
}

bool system_ensure_directory_tree_exists(
    const char *directory)
{
#   warning TODO: reference other platform implementations

    UNUSED(directory);

    return false;
}

void *system_calloc(
    size_t num,
    size_t size)
{
#ifdef _WIN32

    return GlobalAlloc(0x40u, num * size);

#else
#   warning TODO: reference other platform implementations

    return calloc(num, size);

#endif
}

void *system_malloc(
    size_t size)
{
#ifdef _WIN32

    return GlobalAlloc(0, size);

#else
#   warning TODO: reference other platform implementations

    return malloc(size);
    
#endif
}

void system_free(
    void *pointer)
{
#ifdef _WIN32

    LocalFree(pointer);

#else
#   warning TODO: reference other platform implementations

    free(pointer);
    
#endif
}

void *system_realloc(
    void *pointer,
    size_t size)
{
#ifdef _WIN32

    if (!pointer)
        return GlobalAlloc(0, size);
    
    if (size)
        return GlobalReAlloc(pointer, size, 2u);
    
    LocalFree(pointer);

    return 0;

#else
#   warning TODO: reference other platform implementations

    return realloc(pointer, size);
    
#endif
}

size_t system_get_used_memory_size(
    void *pointer)
{
#ifdef _WIN32

    return LocalSize(pointer);

#else
#   warning TODO: not implemented; reference other platform implementations

    return 0;
    
#endif
}

void system_memory_information_get(
    struct system_memory_information *information)
{
#ifdef _WIN32
#   warning TODO

    int64_t v1;       // r31
    int64_t v2;       // r9
    _MEMORYSTATUS v3; // [sp+50h] [-40h] BYREF

    LODWORD(v1) = 0;
    HIDWORD(v1) = information;
    v3.dwMemoryLoad = 0;
    *(_QWORD *)&v3.dwTotalPhys = v1;
    *(_QWORD *)&v3.dwTotalPageFile = v1;
    *(_QWORD *)&v3.dwTotalVirtual = v1;
    v3.dwLength = 32;
    GlobalMemoryStatus(&v3);
    v2 = *(_QWORD *)&v3.dwTotalPhys;
    *(_QWORD *)HIDWORD(v1) = 0i64;
    *(_DWORD *)HIDWORD(v1) = v2;
    *(_DWORD *)(HIDWORD(v1) + 4) = HIDWORD(v2);

#elif defined(XBOX)

    SIZE_T result; // eax
    MEMORYSTATUS Buffer; // [esp+4h] [ebp-20h] BYREF

    memset(&Buffer, 0, 32);
    Buffer.dwLength = 32;
    GlobalMemoryStatus(&Buffer);
    csmemset(a1, 0, 8);
    result = Buffer.dwTotalPhys;
    *a1 = Buffer.dwAvailPhys;
    a1[1] = result;
    return result;

#else
#   warning TODO: not implemented; reference other platform implementations
#endif
}

void system_show_wait_cursor(
    void)
{
#   warning TODO: reference other platform implementations
}

void system_alert(
    const char *prompt)
{
#   warning TODO: reference other platform implementations
}

void system_kill_screen_saver(
    void)
{
#   warning TODO: reference other platform implementations
}

int system_get_process_id(
    void)
{
#   warning TODO: reference other platform implementations

    return 0;
}

/* ---------- private code */

#ifdef _WIN32
static char *exception_code_get_string(
    unsigned int exception_code)
{
    char *result;    // r3
    unsigned int v3; // r11
    unsigned int v4; // r11
    unsigned int v5; // r11

    result = NULL;

    if (exception_code > 0xC000008F)
    {
        v5 = exception_code + 0x3FFFFF70;

        if (v5 <= 6)
        {
            switch (v5)
            {
            case 1u:
                result = "EXCEPTION_FLT_OVERFLOW";
                break;
            case 2u:
                result = "EXCEPTION_FLT_STACK_CHECK";
                break;
            case 3u:
                result = "EXCEPTION_FLT_UNDERFLOW";
                break;
            case 4u:
                result = "EXCEPTION_INT_DIVIDE_BY_ZERO";
                break;
            case 5u:
                result = "EXCEPTION_INT_OVERFLOW";
                break;
            default:
                if (v5)
                    result = "EXCEPTION_PRIV_INSTRUCTION";
                else
                    result = "EXCEPTION_FLT_INVALID_OPERATION";
                break;
            }
        }
    }
    else if (exception_code == 0xC000008F)
    {
        result = "EXCEPTION_FLT_INEXACT_RESULT";
    }
    else if (exception_code > 0xC0000025)
    {
        v4 = exception_code + 0x3FFFFF74;

        if (v4)
        {
            if (v4 == 1)
            {
                result = "EXCEPTION_FLT_DENORMAL_OPERAND";
            }
            else if (v4 == 2)
            {
                result = "EXCEPTION_FLT_DIVIDE_BY_ZERO";
            }
        }
        else
        {
            result = "EXCEPTION_ARRAY_BOUNDS_EXCEEDED";
        }
    }
    else if (exception_code == 0xC0000025)
    {
        result = "EXCEPTION_NONCONTINUABLE_EXCEPTION";
    }
    else if (exception_code > 0x80000004)
    {
        if (exception_code == 0xC0000005)
            result = "EXCEPTION_ACCESS_VIOLATION";
    }
    else if (exception_code == 0x80000004)
    {
        result = "EXCEPTION_SINGLE_STEP";
    }
    else
    {
        v3 = exception_code + 0x7FFFFFFE;

        if (v3)
        {
            if (v3 == 1)
                result = "EXCEPTION_BREAKPOINT";
        }
        else
        {
            result = "EXCEPTION_DATATYPE_MISALIGNMENT";
        }
    }

    return result;
}

static int generic_exception_filter(
    unsigned int exception_code,
    EXCEPTION_POINTERS *exception_information)
{
    stack_walk_with_context(0, 0, exception_information->ContextRecord);
    return 1;
}
#endif

static void initialize_scratch_disk_root(
    void)
{
    memset(scratch_disk_root, 0, sizeof(scratch_disk_root));

    // TODO: reference other platform implementations to see what else is done here
    strncpy(scratch_disk_root, "d:", sizeof(scratch_disk_root) - 1);
}
