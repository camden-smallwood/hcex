#pragma once

/* ---------- structures */

struct dynamic_array
{
    size_t element_size;
    size_t count;
    void *elements;
};

/* ---------- prototypes/ARRAY.C */

void dynamic_array_new(struct dynamic_array *array, size_t element_size);
bool dynamic_array_resize(struct dynamic_array *array, size_t count);
void dynamic_array_delete(struct dynamic_array *array);
int dynamic_array_add_element(struct dynamic_array *array);
void *dynamic_array_get_element(const struct dynamic_array *array, int index, size_t element_size);
void dynamic_array_delete_element(struct dynamic_array *array, int index);

void static_array_new(size_t *count, void *elements, size_t element_size, size_t maximum_count);
bool static_array_resize(size_t *count, void *elements, size_t element_size, size_t maximum_count, size_t new_count);
int static_array_add_element(size_t *count, void *elements, size_t element_size, size_t maximum_count);
void *static_array_get_element(size_t count, const void *elements, size_t element_size, int index);
void static_array_delete_element(size_t *count, const void *elements, size_t element_size, int index);
