#pragma once

/* ---------- structures */

struct terminal_gets_state
{
    int16_t key_count;
    struct key_stroke keys[32];
    real_argb_color color;
    char prompt[32];
    char result[256];
    struct edit_text edit;
};

/* ---------- prototypes/TERMINAL.C */

void terminal_initialize(void);
void terminal_dispose(void);
long terminal_new_line(void);
void terminal_remove_line(int line_index);
void terminal_clear(void);
bool terminal_gets_active(void);
bool terminal_gets_begin(struct terminal_gets_state *state);
void terminal_gets_end(struct terminal_gets_state *state);
void terminal_gets_insert_string(struct terminal_gets_state *state, char *string);
bool terminal_update(void);
void terminal_update_input(void);
void terminal_update_output(void);
rectangle2d convert_to_title_safe_pixel_bounds(rectangle2d *bounds);
void terminal_draw(void);
void terminal_printf(const real_argb_color *color, const char *format, ...);
void ship_terminal_printf(const real_argb_color *color, const char *format, ...);
