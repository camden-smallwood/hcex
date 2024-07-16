#pragma once

/* ---------- prototypes/ERRORS.C */

void errors_initialize(void);
void errors_dispose(void);
bool errors_handle(void);
void errors_output_to_debug_file(bool output_to_debug_file);
void errors_overflow_suppression_enable(bool overflow_suppression);
void errors_suppress_all_enable(bool suppression);
const char *error_get(void);
void errors_clear(void);
void write_to_error_file(char *string, bool date);
