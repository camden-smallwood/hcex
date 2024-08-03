#include "cseries/cseries.h"
#include "memory/data.h"
#include "interface/terminal.h"

/* ---------- private variables */

static bool terminal_render_enable;
static const int terminal_tab_stops[3];

struct
{
    bool initialized;
    struct data_array *output_lines;
    int newest_output_line_index;
    int oldest_output_line_index;
    struct terminal_gets_state *input_state;
    bool insertion_point_visible;
    int last_insertion_point_toggle;
} static terminal_globals;

/* ---------- public code */

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

rectangle2d convert_to_title_safe_pixel_bounds(
    rectangle2d *bounds)
{
    rectangle2d output_bounds;

#error TODO
}

void terminal_draw(
    void)
{
    char buffer[288];
    rectangle2d terminal_gets_bounds;
    rectangle2d terminal_render_bounds;
    rectangle2d line_bounds;
    real_argb_color color;

#error TODO
}

void terminal_printf(
    const real_argb_color *color,
    const char *format,
    ...)
{
    real_argb_color default_terminal_printf_color;
    char *arglist;

#error TODO
}

void ship_terminal_printf(
    const real_argb_color *color,
    const char *format,
    ...)
{
    real_argb_color default_terminal_printf_color;
    char *arglist;

#error TODO
}
