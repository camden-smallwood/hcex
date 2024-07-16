#include "cseries/cseries.h"
#include "cseries/errors.h"

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
    
    size_t message_buffer_size;
    char message_buffer[4096];
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
}

void errors_dispose(
    void)
{
    // stack_walk_dispose();
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
