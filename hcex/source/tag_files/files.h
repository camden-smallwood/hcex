#pragma once

/* ---------- constants */

enum
{
    FILE_REFERENCE_SIGNATURE = 'filo',
    MAXIMUM_FILENAME_LENGTH = 255,
};

enum /* file reference locations */
{
    _file_reference_application_relative,
    _file_reference_cd_relative,
    _file_reference_absolute,
    NUMBER_OF_FILE_REFERENCE_LOCATIONS
};

enum /* file reference info flags */
{
    _has_filename_bit,
    NUMBER_OF_REFERENCE_INFO_FLAGS
};

enum /* file name flags */
{
    _name_directory_bit,
    _name_parent_directory_bit,
    _name_filename_bit,
    _name_extension_bit,
    NUMBER_OF_NAME_FLAGS
};

enum /* file permission flags */
{
    _permission_read_bit,
    _permission_write_bit,
    _permission_append_bit,
    NUMBER_OF_PERMISSION_FLAGS
};

enum /* find files flags */
{
    _find_files_recursive_bit,
    _find_files_enumerate_directories_bit,
    NUMBER_OF_FIND_FILES_FLAGS
};

/* ---------- structures */

struct file_reference
{
    tag signature;
    uint16_t flags;
    int16_t location;

    char path[MAXIMUM_FILENAME_LENGTH + 1];

#if defined(PLATFORM_WINDOWS)
    HANDLE handle;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
    int fd;
#endif
};

struct file_last_modification_date
{
#if defined(PLATFORM_WINDOWS)
    FILETIME filetime;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
    struct timespec timespec;
#endif
};

/* ---------- prototypes/FILES.C */

void file_location_set_volume(int location, const char *volume_name);

void file_reference_verify(const struct file_reference *file);

struct file_reference *file_reference_create(struct file_reference *reference, int location);
struct file_reference *file_reference_create_from_path(struct file_reference *reference, const char *path, bool directory);
struct file_reference *file_reference_create_from_path_absolute(struct file_reference *reference, const char *path, bool directory);
struct file_reference *file_reference_copy(struct file_reference *destination, const struct file_reference *source);
struct file_reference *file_reference_add_directory(struct file_reference *reference, const char *directory);
struct file_reference *file_reference_set_name(struct file_reference *reference, const char *name);
int file_reference_get_location(const struct file_reference *reference);
char *file_reference_get_name(const struct file_reference *reference, unsigned int flags, char *name);
bool file_references_equal(const struct file_reference *reference0, const struct file_reference *reference1);

size_t find_files(unsigned int flags, const struct file_reference *directory, size_t maximum_count, struct file_reference *references);

void *file_read_into_memory(struct file_reference *reference, uint64_t *size);
void file_printf(struct file_reference *file, char *format, ...);

void directory_create_or_delete_contents(const char *directory_name);

bool datastore_read(const char *file_name, const char *field_name, size_t length, void *data);
bool datastore_write(const char *file_name, const char *field_name, size_t length, const void *data);

/* ---------- prototypes/FILES_WINDOWS_XBOX.C */

bool file_create(struct file_reference *full_path);
bool file_delete(struct file_reference *full_path);
bool file_exists(const struct file_reference *full_path);

bool file_rename(struct file_reference *old_full_path, const char *new_full_path);

bool file_open(struct file_reference *file, unsigned int flags);
bool file_close(struct file_reference *file);

uint64_t file_get_position(const struct file_reference *file);
bool file_set_position(const struct file_reference *file, uint64_t position);

uint64_t file_get_eof(const struct file_reference *file);
bool file_set_eof(const struct file_reference *file, uint64_t position);

bool file_read(const struct file_reference *file, size_t count, void *buffer);
bool file_write(const struct file_reference *file, size_t count, const void *buffer);

bool file_read_from_position(const struct file_reference *file, uint64_t position, size_t count, void *buffer);
bool file_write_to_position(const struct file_reference *file, uint64_t position, size_t count, const void *buffer);

bool file_get_last_modification_date(const struct file_reference *file, struct file_last_modification_date *date);
int file_compare_last_modification_dates(struct file_last_modification_date *date1, struct file_last_modification_date *date2);

bool file_get_size(const struct file_reference *file, uint64_t *size);

void find_files_start(unsigned int flags, const struct file_reference *directory);
bool find_files_next(struct file_reference *file, struct file_last_modification_date *date);

void file_path_add_name(char *path, const char *name);
void file_path_add_extension(char *path, const char *extension);
void file_path_remove_name(char *path);
void file_path_split(char *path, char **directory, char **parent_directory, char **filename, char **extension, bool has_filename);

void file_location_get_full_path(int location, char *path, char *full_path);

bool file_read_only(struct file_reference *file);
void file_error(const char *function_name, const struct file_reference *file);
