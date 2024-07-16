#pragma once

/* ---------- structures */

struct system_unique_identifier
{
    uint8_t data[16];
};

struct system_memory_information
{
    size_t free;
    size_t total;
};

/* ---------- constants */

extern const struct system_unique_identifier system_unique_identifier_zero;

/* ---------- prototypes/CSERIES_WINDOWS.C */

void cseries_platform_initialize(void);

void system_exit(int code);

void system_unique_identifier_get(struct system_unique_identifier *identifier);
bool system_unique_identifiers_equal(const struct system_unique_identifier *identifier1, const struct system_unique_identifier *identifier2);

void system_timer_init(void);
uint32_t system_seconds(void);
uint32_t system_milliseconds(void);
uint64_t system_microseconds(void);
int64_t system_clocks(void);
uint32_t system_clocks_to_seconds(int64_t clocks);
uint32_t system_clocks_to_milliseconds(int64_t clocks);
uint64_t system_clocks_to_microseconds(int64_t clocks);
double system_clock_delta_seconds_real(int64_t a, int64_t b);
uint32_t system_clock_delta_seconds(int64_t a, int64_t b);
uint32_t system_clock_delta_milliseconds(int64_t a, int64_t b);
uint32_t system_clock_delta_microseconds(int64_t a, int64_t b);
size_t system_get_date_time_string(char *date_time_string, size_t max_length_in_bytes);

void system_get_user_name(char *name, size_t maximum_length);

char *system_get_scratch_disk_root(void);
bool system_ensure_directory_tree_exists(const char *directory);

void *system_calloc(size_t num, size_t size);
void *system_malloc(size_t size);
void system_free(void *pointer);
void *system_realloc(void *pointer, size_t size);
size_t system_get_used_memory_size(void *pointer);
void system_memory_information_get(struct system_memory_information *information);

void system_show_wait_cursor(void);
void system_alert(const char *prompt);
void system_kill_screen_saver(void);
int system_get_process_id(void);
