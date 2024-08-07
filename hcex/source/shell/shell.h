#pragma once

/* ---------- prototypes */

bool shell_running_import_tool(void);
bool shell_application_is_paused(void);
void shell_screen_pause(bool paused);

bool shell_platform_initialize(void);
void shell_platform_dispose(void);
void shell_platform_verify(void);

bool shell_initialize(void);
void shell_dispose(void);
void shell_idle(void);

char *shell_get_command_line(void);
bool shell_get_clipboard_text(char * buffer, size_t length);
