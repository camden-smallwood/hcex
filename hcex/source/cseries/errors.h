#pragma once

/* ---------- constants */

enum /* error message priorities */
{
    _error_message_priority_out_of_memory,
    _error_message_priority_warning,
    _error_message_priority_assert,
    _error_message_priority_critical,
    NUMBER_OF_ERROR_MESSAGE_PRIORITIES
};

enum
{
    MAXIMUM_SYMBOL_NAME_LENGTH = 256,
    MAXIMUM_NUMBER_OF_STACK_FRAMES = 64,
    MAXIMUM_LINE_LENGTH = 0x4000,
    
    SYMBOL_ALLOCATION_BLOCK_SIZE = 0x1000,
    SYMBOL_STRING_BLOCK_SIZE = 0x4000,

    ERROR_LOGGING_LEVEL = _error_message_priority_assert,
};

struct debug_symbol_table
{
    long number_of_symbols;
    char *string_storage;
    struct debug_symbol *symbols;
};

struct debug_symbol
{
    uint32_t address;
    uint32_t rva_base;
    uint32_t name_string_offset;
    uint32_t library_object_string_offset;
};

/* ---------- prototypes/ERRORS.C */

void errors_initialize(void);
void errors_dispose(void);

void error(int priority, char *fmt, ...);
bool errors_handle(void);

void errors_output_to_debug_file(bool output_to_debug_file);
void errors_overflow_suppression_enable(bool overflow_suppression);
void errors_suppress_all_enable(bool suppression);

const char *error_get(void);
void errors_clear(void);

void write_to_error_file(char *string, bool date);

/* ---------- prototypes/STACK_WALK_WINDOWS.C */

void stack_walk_initialize(void);
void stack_walk_dispose(void);
void stack_walk(int levels_to_ignore);
