#pragma once

/* ---------- constants */

enum /* tag field types */
{
    _field_string,
    _field_char_integer,
    _field_short_integer,
    _field_long_integer,
    _field_angle,
    _field_tag,
    _field_enum,
    _field_flags,
    _field_word_flags,
    _field_byte_flags,
    _field_point2d,
    _field_rectangle2d,
    _field_rgb_pixel32,
    _field_argb_pixel32,
    _field_real,
    _field_real_fraction,
    _field_real_point2d,
    _field_real_point3d,
    _field_real_vector2d,
    _field_real_vector3d,
    _field_real_quaternion,
    _field_real_euler_angles2d,
    _field_real_euler_angles3d,
    _field_real_plane2d,
    _field_real_plane3d,
    _field_real_rgb_color,
    _field_real_argb_color,
    _field_real_hsv_color,
    _field_real_ahsv_color,
    _field_short_integer_bounds,
    _field_angle_bounds,
    _field_real_bounds,
    _field_real_fraction_bounds,
    _field_tag_reference,
    _field_block,
    _field_short_block_index,
    _field_long_block_index,
    _field_data,
    _field_start_array,
    _field_end_array,
    _field_pad,
    _field_skip,
    _field_explanation,
    _field_custom,
    _field_terminator,
    NUMBER_OF_TAG_FIELD_TYPES
};

enum /* tag data definition flags */
{
    _tag_data_cached_bit,
    _tag_data_string_bit,
    _tag_data_not_added_to_monolithic_file_bit,
    NUMBER_OF_TAG_DATA_DEFINITION_FLAGS
};

enum /* tag group flags */
{
    _tag_group_is_game_critical_bit,
    _tag_group_is_local_bit,
    _tag_group_is_not_editable_bit,
    _tag_group_can_be_reloaded_bit,
    NUMBER_OF_TAG_GROUP_FLAGS
};

/* ---------- structures */

struct tag_field
{
    int16_t type;
    char *name;
    void *definition;
};

struct tag_block
{
    int32_t count;
    
    #warning `address` and `definition` need to be 32-bit on all platforms. Check MCC ptr32_t implementation?
    void *address;
    struct tag_block_definition *definition;
};

struct tag_block_definition
{
    char *name;
    uint32_t flags;
    int32_t maximum_element_count;
    int32_t element_size;
    void *default_element;
    struct tag_field *fields;
    void (*byte_swap_block)(void *);
    bool (*postprocess_block)(void *, bool);
    char *(*format_block)(int32_t, struct tag_block *, int32_t, char *);
    void (*delete_block)(struct tag_block *, int32_t);
    intptr_t *byte_swap_codes;
};

struct tag_data
{
    int32_t size;
    uint32_t pad;
    int32_t file_offset;

    #warning `address` and `definition` need to be 32-bit on all platforms. Check MCC ptr32_t implementation?
    void *address;
    struct tag_data_definition *definition;
};

struct tag_data_definition
{
    char *name;
    uint32_t flags;
    int32_t maximum_size;
    void (*byte_swap_data)(void *, void *, int32_t);
};

struct tag_reference
{
    tag group_tag;

    #warning `name` needs to be 32-bit on all platforms. Check MCC ptr32_t implementation?
    char *name;

    int32_t name_length;
    int32_t index;
};

struct tag_group
{
    char *name;
    uint32_t flags;
    tag group_tag;
    tag parent_tag;
    int16_t version;
    void (*postprocess_tag)(int32_t, bool);
    struct tag_block_definition *header_block_definition;
    tag child_tags[16];
    int16_t child_count;
};

/* ---------- prototypes/TAG_GROUPS.C */

char *tag_data_get_pointer(
    const struct tag_data *data,
    size_t offset,
    size_t size);

char *tag_block_get_element_with_size(
    const struct tag_block *block,
    intptr_t index,
    size_t element_size);
