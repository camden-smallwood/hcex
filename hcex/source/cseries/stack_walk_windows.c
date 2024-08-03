#include "cseries/cseries.h"
#include "cseries/errors.h"

#if defined(PLATFORM_WINDOWS)
#   include <winnt.h>
#else
// #   error unsupported platform
#endif

#include <stdio.h>

/* ---------- private variables */

unsigned long *old_ebp;

struct _stack_walk_globals
{
    long fixup;
    unsigned char disregard_symbol_names;
    struct debug_symbol_table symbol_table;
} stack_walk_globals;

/* ---------- public code */

// void stack_walk_initialize(void);
// void stack_walk_dispose(void);
// long stack_walk_global_function_offset(void);
// void stack_walk_disregard_symbol_names(bool disregard);
// void stack_walk(int levels_to_ignore);
// void stack_walk_with_context(FILE *error_stream, short levels_to_ignore, CONTEXT *context_pointer)
// {
//     long frame_number;
//     unsigned long addresses[64];
// }
// int32_t symbol_sort_proc(const void *elem1, const void *elem2);
// bool load_symbol_table(char *filename, struct debug_symbol_table *symbol_table, char *timestamp_str)
// {
//     char line[16384];
//     char last_object_file_name[256];
//     char *end_str;
//     char library_object_file_name[256];
//     char symbol_name[256];
// }
// void free_symbol_table(struct debug_symbol_table *symbol_table);
// char *symbol_name_from_address(unsigned long fake_address, struct debug_symbol_table *symbol_table)
// {
//     char symbol_buffer[16384];
// }
// unsigned long base_address_from_symbol_name(const char *name, struct debug_symbol_table *symbol_table);
// unsigned char is_valid_ebp(void);
// unsigned long walk_up(void);
// void initialize_stack_walk(CONTEXT *context);
// void walk_stack_context(unsigned long *routine_addresses, unsigned long number_of_levels, unsigned long ignore_levels, unsigned long *levels_dumped);
// void walk_stack(unsigned long *routine_addresses, unsigned long number_of_levels, unsigned long ignore_levels, unsigned long *levels_dumped);
