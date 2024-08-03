#include "cseries/cseries.h"
#include "cseries/errors.h"
#include "interface/terminal.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/* ---------- private constants */

enum /* developer modes */
{
    _developer_mode_off,
    _developer_mode_errors_enabled,
    _developer_mode_logging_enabled,
    _developer_mode_metrics_enabled,
    _developer_mode_conprint_enabled,
    _developer_mode_full = INT8_MAX,
};

enum
{
    ERROR_MESSAGE_BUFFER_MAXIMUM_SIZE = 4096,
    ERROR_OVERFLOW_RESET_TIME = 900,
    ERROR_OVERFLOW_COUNT = 10,
};

/* ---------- private structures */

typedef struct error_global_data
{
    bool delayed;
    bool output_to_debug_file;
    bool display_state;
    bool recursion_lock;
    bool overflow_suppression;
    bool suppress_all;
    
    uint8_t developer_mode;

    uint32_t last_overflow_time;
    uint32_t overflow_count;

    size_t message_buffer_size;
    char message_buffer[ERROR_MESSAGE_BUFFER_MAXIMUM_SIZE];
} error_global_data;

/* ---------- private variables */

static error_global_data error_globals;

static bool find_all_fucked_up_shit = false;
static size_t fucked_up_shit_count = 0;

/* ---------- private prototypes */

static void reset_error_state(void);

/* ---------- public code */

void errors_initialize(
    void)
{
    memset(&error_globals, 0, sizeof error_globals);

    error_globals.developer_mode = _developer_mode_full;

    error_globals.output_to_debug_file = true;
    error_globals.overflow_suppression = true;
    error_globals.suppress_all = false;

    reset_error_state();
    stack_walk_initialize();
}

void errors_dispose(
    void)
{
    stack_walk_dispose();
}

void error(
    int priority,
    char *fmt,
    ...)
{
    assert(priority >= 0 && priority < NUMBER_OF_ERROR_MESSAGE_PRIORITIES);

    va_list va;
    va_start(va, fmt);

    if (error_globals.overflow_suppression &&
        priority == _error_message_priority_assert)
    {
        uint32_t overflow_time = system_milliseconds();

        if (overflow_time > error_globals.last_overflow_time + ERROR_OVERFLOW_RESET_TIME)
            error_globals.overflow_count = 0;

        error_globals.last_overflow_time = overflow_time;

        if (error_globals.overflow_count == ERROR_OVERFLOW_COUNT)
            terminal_printf(global_real_argb_white, "too many errors, only printing to debug.txt");

        if (++error_globals.overflow_count >= ERROR_OVERFLOW_COUNT)
            priority = _error_message_priority_critical;
    }

    if (!error_globals.recursion_lock)
    {
        error_globals.recursion_lock = true;

        if (priority == _error_message_priority_warning)
            error_globals.delayed = true;

        if (fmt)
        {
            char buffer[1024];
            vsprintf(buffer, fmt, va);
            strcat(buffer, "\r\n");

            if (priority != _error_message_priority_critical)
                terminal_printf(global_real_argb_white, "%s", buffer);

            write_to_error_file(buffer, true);

            size_t new_size = strlen(buffer);
            size_t message_buffer_size = error_globals.message_buffer_size;

            if (new_size + error_globals.message_buffer_size >= ERROR_MESSAGE_BUFFER_MAXIMUM_SIZE)
            {
                const char *copy = "[...too many errors to print...]\r\n";
                size_t copy_size = strlen(copy);
                
                size_t total_size = copy_size + new_size + sizeof(buffer);

                if (total_size > error_globals.message_buffer_size - 1)
                    total_size = error_globals.message_buffer_size - 1;

                char *prefix = strchr(&error_globals.message_buffer[total_size], '\n');

                size_t prefix_start;

                if (prefix)
                    prefix_start = prefix - error_globals.message_buffer + 1;
                else
                    prefix_start = error_globals.message_buffer_size;

                size_t prefix_size = error_globals.message_buffer_size - prefix_start;

                assert(prefix_size + copy_size + new_size < ERROR_MESSAGE_BUFFER_MAXIMUM_SIZE);

                strncpy(error_globals.message_buffer, copy, copy_size);

                if (prefix_size > 0)
                    memmove(&error_globals.message_buffer[copy_size], prefix, prefix_size);

                message_buffer_size = copy_size + prefix_size;
                error_globals.message_buffer[prefix_size + copy_size] = 0;
                error_globals.message_buffer_size = message_buffer_size;
            }

            if (message_buffer_size + new_size < ERROR_MESSAGE_BUFFER_MAXIMUM_SIZE)
            {
                strcpy(&error_globals.message_buffer[message_buffer_size], buffer);
                error_globals.message_buffer_size += new_size;
            }
        }

        if (priority == _error_message_priority_out_of_memory)
        {
            #warning TODO: find where this exit code came from
            system_exit(-4998);
        }

        error_globals.recursion_lock = false;
    }
}

bool errors_handle(
    void)
{
    bool result = error_globals.delayed;

    errors_clear();

    return result;
}

void errors_output_to_debug_file(
    bool output_to_debug_file)
{
    error_globals.output_to_debug_file = output_to_debug_file;
}

void errors_overflow_suppression_enable(
    bool overflow_suppression)
{
    error_globals.overflow_suppression = overflow_suppression;
}

void errors_suppress_all_enable(
    bool suppression)
{
    error_globals.suppress_all = suppression;
}

const char *error_get(
    void)
{
    return error_globals.message_buffer;
}

void errors_clear(
    void)
{
    reset_error_state();
}

void write_to_error_file(char *string, bool date)
{
    static bool first_line = true;

    if (error_globals.developer_mode >= _developer_mode_logging_enabled)
    {
        if (first_line)
        {
            first_line = false;

            write_to_error_file("\r\n\r\n", false);
            write_to_error_file("halo xbox 01.00.01.0563(CACHE) ----------------------------------------------\r\n", true);

            char buffer[1056];

            csprintf(buffer, "reference function: %s\r\n", "_write_to_error_file");
            write_to_error_file(buffer, true);

            csprintf(buffer, "reference address: %x\r\n", write_to_error_file);
            write_to_error_file(buffer, true);
        }

        if (error_globals.output_to_debug_file)
        {
            FILE *file = fopen("d:\\debug.txt", "a+b");

            if (file)
            {
                if (date)
                {
                    time_t t = time(NULL);
                    struct tm *tm = localtime(&t);

                    if (tm)
                    {
                        fprintf(
                            file,
                            "%02d.%02d.%02d %02d:%02d:%02d    ",
                            tm->tm_mon + 1,
                            tm->tm_mday,
                            tm->tm_year % 100,
                            tm->tm_hour,
                            tm->tm_min,
                            tm->tm_sec);
                    }
                    else
                    {
                        fprintf(file, "<TIME UNAVAILABLE>    ");
                    }
                }

                fprintf(file, "%s", string);
                fclose(file);
            }
        }
    }
}

/* ---------- private code */

static void reset_error_state(
    void)
{
    error_globals.delayed = false;
    error_globals.message_buffer_size = 0;
}
