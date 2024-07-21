#include "cseries/cseries.h"
#include "tag_files/files.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- private constants */

enum
{
    DATASTORE_MAX_FIELD_NAME_SIZE = 255,
    DATASTORE_MAX_DATA_SIZE = 255,
    DATASTORE_MAX_ENTRY_COUNT = 200,
};

/* ---------- private structures */

struct datastore_entry
{
    char name[DATASTORE_MAX_FIELD_NAME_SIZE];
    char data[DATASTORE_MAX_DATA_SIZE];
};

struct datastore
{
    struct datastore_entry entry[DATASTORE_MAX_ENTRY_COUNT];
};

/* ---------- private variables */

static char file_location_volume_names[NUMBER_OF_FILE_REFERENCE_LOCATIONS][MAXIMUM_FILENAME_LENGTH + 1];

/* ---------- public code */

void file_location_set_volume(
    int location,
    const char *volume_name)
{
    assert(location > 0 && location < NUMBER_OF_FILE_REFERENCE_LOCATIONS);
    assert(strnlen(file_location_volume_names[location], MAXIMUM_FILENAME_LENGTH) == 0);
    assert(strlen(volume_name) <= MAXIMUM_FILENAME_LENGTH);

    strncpy(file_location_volume_names[location], volume_name, MAXIMUM_FILENAME_LENGTH);
    file_location_volume_names[location][MAXIMUM_FILENAME_LENGTH] = '\0';
}

struct file_reference_info *file_reference_get_info(
    struct file_reference *reference)
{
    struct file_reference_info *info = (struct file_reference_info *)reference;

    assert(info);
    assert(info->signature == FILE_REFERENCE_SIGNATURE);
    assert(VALID_FLAGS(info->flags, NUMBER_OF_REFERENCE_INFO_FLAGS));
    assert(info->location >= NONE && info->location < NUMBER_OF_FILE_REFERENCE_LOCATIONS);

    return info;
}

struct file_reference *file_reference_create(
    struct file_reference *reference,
    int location)
{
    assert(reference);
    assert(location >= NONE && location < NUMBER_OF_FILE_REFERENCE_LOCATIONS);

    memset(reference, 0, sizeof(struct file_reference));

    struct file_reference_info *info = (struct file_reference_info *)reference->data;
    info->location = location;
    info->signature = FILE_REFERENCE_SIGNATURE;

    return reference;
}

struct file_reference *file_reference_create_from_path(
    struct file_reference *reference,
    const char *path,
    bool directory)
{
    assert(reference);

    memset(reference, 0, sizeof(struct file_reference));

    struct file_reference_info *info = (struct file_reference_info *)reference->data;
    info->location = NONE;
    info->signature = FILE_REFERENCE_SIGNATURE;

    if (directory)
        file_path_add_name(info->path, path);
    else
        file_reference_set_name(reference, path);

    return reference;
}

struct file_reference *file_reference_create_from_path_absolute(
    struct file_reference *reference,
    const char *path,
    bool directory)
{
    assert(reference);

    memset(reference, 0, sizeof(struct file_reference));

    struct file_reference_info *info = (struct file_reference_info *)reference->data;
    info->location = _file_reference_absolute;
    info->signature = FILE_REFERENCE_SIGNATURE;

    if (directory)
        file_path_add_name(info->path, path);
    else
        file_reference_set_name(reference, path);

    return reference;
}

struct file_reference *file_reference_copy(
    struct file_reference *destination,
    const struct file_reference *source)
{
    file_reference_get_info((struct file_reference *)source);

    memcpy(destination, source, sizeof(struct file_reference));

    return destination;
}

struct file_reference *file_reference_add_directory(
    struct file_reference *reference,
    const char *directory)
{
    struct file_reference_info *info = file_reference_get_info(reference);

    assert(directory);
    assert(!TEST_FLAG(info->flags, _has_filename_bit));

    file_path_add_name(&reference->data[8], directory);

    return reference;
}

struct file_reference *file_reference_set_name(
    struct file_reference *reference,
    const char *name)
{
    struct file_reference_info *info = file_reference_get_info(reference);

    assert(name);

    if (TEST_FLAG(info->flags, _has_filename_bit))
        file_path_remove_name(info->path);

    file_path_add_name(info->path, name);

    SET_FLAG(info->flags, _has_filename_bit, true);

    return reference;
}

int file_reference_get_location(
    const struct file_reference *reference)
{
    return file_reference_get_info((struct file_reference *)reference)->location;
}

char *file_reference_get_name(
    const struct file_reference *reference,
    unsigned int flags,
    char *name)
{
    struct file_reference_info *info = file_reference_get_info((struct file_reference *)reference);

    assert(name);
    assert(VALID_FLAGS(info->flags, NUMBER_OF_NAME_FLAGS));
    assert(flags);
    assert(flags != (FLAG(_name_directory_bit) | FLAG(_name_extension_bit)));
    assert(!TEST_FLAG(flags, _name_directory_bit) || !TEST_FLAG(flags, _name_parent_directory_bit));

    char full_path[MAXIMUM_FILENAME_LENGTH];
    memset(full_path, 0, sizeof(full_path));

    file_location_get_full_path(info->location, info->path, full_path);

    char *directory, *parent_directory, *filename, *extension;
    file_path_split(
        full_path,
        &directory,
        &parent_directory,
        &filename,
        &extension,
        TEST_FLAG(info->flags, _has_filename_bit));

    *name = '\0';

    if (TEST_FLAG(flags, _name_directory_bit))
        file_path_add_name(name, directory);

    if (TEST_FLAG(flags, _name_parent_directory_bit))
        file_path_add_name(name, parent_directory);

    if (TEST_FLAG(flags, _name_filename_bit))
        file_path_add_name(name, filename);

    if (TEST_FLAG(flags, _name_extension_bit))
        file_path_add_extension(name, extension);

    return name;
}

bool file_references_equal(
    const struct file_reference *reference0,
    const struct file_reference *reference1)
{
    struct file_reference_info *info0 = file_reference_get_info((struct file_reference *)reference0);
    struct file_reference_info *info1 = file_reference_get_info((struct file_reference *)reference1);

    return info0->location == info1->location && strcmp(info0->path, info1->path) == 0;
}

size_t find_files(
    unsigned int flags,
    const struct file_reference *directory,
    size_t maximum_count,
    struct file_reference *references)
{
    assert(maximum_count > 0);
    assert(references);

    find_files_start(flags, directory);

    size_t file_count = 0;

    while (file_count < maximum_count)
    {
        if (!find_files_next(references, NULL))
            break;

        file_count++;
        references++;
    }

    return file_count;
}

void *file_read_into_memory(
    struct file_reference *reference,
    uint64_t *size)
{
    if (!file_open(reference, FLAG(_permission_read_bit)))
        return NULL;

    uint64_t file_size = file_get_eof(reference);
    *size = file_size;

    void *result = malloc(file_size);

    if (result && !file_read(reference, *size, result))
    {
        free(result);
        result = NULL;
    }

    file_close(reference);

    return result;
}

void file_printf(
    struct file_reference *file,
    char *format,
    ...)
{
    va_list va;
    va_start(va, format);

    if (format)
    {
        char buffer[1024];
        vsprintf(buffer, format, va);

        size_t buffer_length = strlen(buffer);
        file_write(file, buffer_length, buffer);

        uint64_t position = file_get_position(file);
        file_set_eof(file, position);
    }

    va_end(va);
}

void directory_create_or_delete_contents(
    const char *directory_name)
{
    struct file_reference reference;
    memset(&reference, 0, sizeof(reference));

    struct file_reference_info *info = (struct file_reference_info *)reference.data;
    info->location = NONE;
    info->signature = FILE_REFERENCE_SIGNATURE;

    file_path_add_name(info->path, directory_name);

    if (file_exists(&reference))
    {
        find_files_start(0, &reference);

        struct file_reference child_reference;
        while (find_files_next(&child_reference, NULL))
            file_delete(&child_reference);
    }
    else
    {
        file_create(&reference);
    }
}

bool datastore_read(
    const char *file_name,
    const char *field_name,
    size_t length,
    void *data)
{
    assert(file_name);
    assert(field_name);
    assert(file_name[0] != '\0');
    assert(field_name[0] != '\0');
    assert(length < DATASTORE_MAX_DATA_SIZE);

    struct file_reference reference;
    memset(&reference, 0, sizeof(reference));

    struct file_reference_info *info = (struct file_reference_info *)reference.data;
    info->location = NONE;
    info->signature = FILE_REFERENCE_SIGNATURE;

    file_reference_set_name(&reference, file_name);

    if (!file_exists(&reference))
        return false;

    uint64_t size = 0;
    struct datastore *datastore = (struct datastore *)file_read_into_memory(&reference, &size);

    if (!datastore)
    {
        file_delete(&reference);
        return false;
    }

    if (size != sizeof(struct datastore))
    {
        free(datastore);
        file_delete(&reference);
        return false;
    }

    for (int i = 0; i < DATASTORE_MAX_ENTRY_COUNT; i++)
    {
        struct datastore_entry *entry = &datastore->entry[i];

        if (strncmp(entry->name, field_name, DATASTORE_MAX_FIELD_NAME_SIZE) == 0)
        {
            memcpy(data, entry->data, length);
            free(datastore);
            return true;
        }
    }

    free(datastore);
    file_delete(&reference);
    return false;
}

bool datastore_write(
    const char *file_name,
    const char *field_name,
    size_t length,
    const void *data)
{
    assert(file_name);
    assert(field_name);
    assert(file_name[0] != '\0');
    assert(field_name[0] != '\0');
    assert(length < DATASTORE_MAX_DATA_SIZE);
    assert(strlen(field_name) < DATASTORE_MAX_FIELD_NAME_SIZE);

    struct file_reference reference;
    memset(&reference, 0, sizeof(reference));

    struct file_reference_info *info = (struct file_reference_info *)reference.data;
    info->location = NONE;
    info->signature = FILE_REFERENCE_SIGNATURE;

    file_reference_set_name(&reference, file_name);

    struct datastore *datastore = NULL;

    if (file_exists(&reference))
    {
        uint64_t size = 0;
        datastore = (struct datastore *)file_read_into_memory(&reference, &size);

        if (!datastore)
        {
            file_delete(&reference);
        }
        else if (size != sizeof(struct datastore))
        {
            free(datastore);
            datastore = NULL;

            file_delete(&reference);
        }
    }

    if (!datastore)
    {
        datastore = (struct datastore *)malloc(sizeof(struct datastore));

        if (!datastore)
            return false;

        memset(datastore, 0, sizeof(struct datastore));
    }

    bool success = false;

    for (int i = 0; i < DATASTORE_MAX_ENTRY_COUNT; i++)
    {
        struct datastore_entry *entry = &datastore->entry[i];

        if (strncmp(entry->name, field_name, DATASTORE_MAX_FIELD_NAME_SIZE) == 0)
        {
            strncpy(entry->name, field_name, DATASTORE_MAX_FIELD_NAME_SIZE);
            memcpy(entry->data, data, length);
            success = true;
            break;
        }
    }

    if (!file_exists(&reference))
        file_create(&reference);

    if (file_open(&reference, FLAG(_permission_write_bit)))
    {
        file_write(&reference, sizeof(struct datastore), datastore);
        file_close(&reference);
    }

    free(datastore);

    assert(success);
    return success;
}
