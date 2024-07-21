#include "cseries/cseries.h"
#include "tag_files/files.h"

#if defined(_WIN32)
#   define WIN32_LEAN_AND_MEAN
#   include <Windows.h>
#elif defined(__APPLE__) && defined(__MACH__)
#   include <sys/stat.h>
#else
#   error unsupported platform
#endif

#include <ctype.h>
#include <string.h>

/* ---------- private code */

#if defined(_WIN32)
char file_last_cd_drive_name[4];
#endif

struct find_files_state
{
    unsigned int flags;
    short depth;
    short location;
    char path[MAXIMUM_FILENAME_LENGTH + 1];
    void *handles[8];

#if defined(_WIN32)
    _WIN32_FIND_DATAA data;
#endif
} find_files_globals;

/* ---------- public code */

bool file_create(
    struct file_reference *file)
{
    struct file_reference_info *info = file_reference_get_info(file);

    char file_name[MAXIMUM_FILENAME_LENGTH - 2];
    memset(file_name, 0, sizeof(file_name));

    file_location_get_full_path(info->location, info->path, file_name);

    if (TEST_FLAG(info->flags, _has_filename_bit))
    {
#if defined(_WIN32)
#warning TODO: finish refactoring

        HANDLE handle = CreateFileA(file_name, 0x40000000, 0, 0, 2, 0x80, 0);

        if (handle != (HANDLE)NONE)
        {
            CloseHandle(handle);
            return true;
        }

#elif defined(__APPLE__) && defined(__MACH__)
#warning TODO

        // mkdir(const char *, mode_t)

#else
#error unsupported platform
#endif
    }
    else
    {
#if defined(_WIN32)
#warning TODO: finish refactoring

        if (CreateDirectoryA(info->path, 0))
            return true;

#else
#error unsupported platform
#endif
    }

#if defined(_WIN32)
#warning TODO: finish refactoring

    error(2, "%s('%s') error 0x%08x", "file_create", info->path, GetLastError());
    SetLastError(0);

#else
#error unsupported platform
#endif

    return false;
}

bool file_delete(
    struct file_reference *file)
{
    struct file_reference_info *info = file_reference_get_info(file);

    char file_name[MAXIMUM_FILENAME_LENGTH - 2];
    memset(file_name, 0, sizeof(file_name));

    file_location_get_full_path(info->location, info->path, file_name);

    if (TEST_FLAG(info->flags, _has_filename_bit))
    {
#if defined(_WIN32)
#warning TODO: finish refactoring

        if (SetFileAttributesA(file_name, 0x80u) && DeleteFileA(file_name))
            return true;

#else
#error unsupported platform
#endif
    }
    else
    {
#if defined(_WIN32)
#warning TODO: finish refactoring

        if (RemoveDirectoryA(file_name))
            return true;

#else
#error unsupported platform
#endif
    }

#if defined(_WIN32)
#warning TODO: finish refactoring

    error(2, "%s('%s') error 0x%08x", "file_delete", info->path, GetLastError());
    SetLastError(0);

#else
#error unsupported platform
#endif

    return false;
}

bool file_exists(
    const struct file_reference *file)
{
    struct file_reference_info *info = file_reference_get_info((struct file_reference *)file);

    char file_name[MAXIMUM_FILENAME_LENGTH - 2];
    memset(file_name, 0, sizeof(file_name));

    file_location_get_full_path(info->location, info->path, file_name);

#if defined(_WIN32)
#warning TODO: finish refactoring

    if (GetFileAttributesA(file_name) != -1)
        return true;

    if (GetLastError() != 2 && GetLastError() != 3)
        file_error((char)"file_exists");

#else
#error unsupported platform
#endif

    return false;
}

bool file_rename(
    struct file_reference *file,
    const char *name)
{
    struct file_reference_info *info = file_reference_get_info(file);

    char old_full_path[MAXIMUM_FILENAME_LENGTH];
    memset(old_full_path, 0, sizeof(old_full_path));

    char new_full_path[MAXIMUM_FILENAME_LENGTH];
    memset(new_full_path, 0, sizeof(new_full_path));

    file_location_get_full_path(info->location, info->path, old_full_path);

    strcpy(new_full_path, old_full_path);

    file_path_remove_name(new_full_path);
    file_path_add_name(new_full_path, name);

#if defined(_WIN32)
#warning TODO: finish refactoring

    if (!MoveFileA(&full_path, &v8))
        return false;
    
#else
#error unsupported platform
#endif

    file_path_remove_name(info->path);
    file_path_add_name(info->path, name);

    return true;
}

bool file_open(
    struct file_reference *file,
    unsigned int flags)
{
    struct file_reference_info *info = file_reference_get_info(file);

    assert(VALID_FLAGS(flags, NUMBER_OF_PERMISSION_FLAGS));
    assert(flags & (FLAG(_permission_read_bit) | FLAG(_permission_write_bit)));
    assert(TEST_FLAG(flags, _permission_write_bit) || !TEST_FLAG(flags, _permission_append_bit));

    char full_path[MAXIMUM_FILENAME_LENGTH - 2];
    memset(full_path, 0, sizeof(full_path));

    file_location_get_full_path(info->location, info->path, full_path);

#if defined(_WIN32)
#warning TODO: finish refactoring

    unsigned int create_file_flags = 0x80000000;

    if ((flags & 1) == 0)
        create_file_flags = 0;

    if ((flags & 2) != 0)
        create_file_flags |= 0x40000000u;

    FileA = CreateFileA(full_path, create_file_flags, 0, 0, 3u, 0x80u, 0);

    if (FileA == (HANDLE)-1)
    {
        LastError = GetLastError();
        error(2, "%s('%s') error 0x%08x", "file_open", info->path, LastError);
        SetLastError(0);
        return false;
    }

    info[1].signature = (unsigned int)FileA;

    if ((flags & 4) == 0)
        return true;

    if (SetFilePointer(FileA, 0, 0, 2u) == -1)
    {
        CloseHandle((HANDLE)info[1].signature);
        info[1].signature = 0;
        LastError = GetLastError();
        error(2, "%s('%s') error 0x%08x", "file_open", info->path, LastError);
        SetLastError(0);
        return false;
    }
#else
#error unsupported platform
#endif

    return true;
}

bool file_close(
    struct file_reference *file)
{
    struct file_reference_info *info = file_reference_get_info(file);

#if defined(_WIN32)
#warning TODO: finish refactoring

    if (CloseHandle((HANDLE)info[1].signature))
    {
        info[1].signature = 0;
        return 1;
    }
    else
    {
        v3 = file_reference_get_info(file);
        LastError = GetLastError();
        error(2, "%s('%s') error 0x%08x", "file_close", v3->path, LastError);
        SetLastError(0);
        return 0;
    }
#else
#error unsupported platform
#endif

    return false;
}

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

void file_location_get_full_path(
    int location,
    char *path,
    char *full_path)
{
    assert(path && full_path);

    full_path[0] = '\0';

#if defined(_WIN32)
#warning TODO: finish refactoring

    if (!path[0] || !path[1] || !path[2] || !isalpha(path[0]) || path[1] != ':' || path[2] != '\\')
        strcpy(full_path, "d:\\");

    strcat(full_path, path);

#elif defined(__APPLE__) && defined(__MACH__)
#warning TODO: finish refactoring

    if (location == _file_reference_absolute)
    {
        strcpy(full_path, path);
    }
    else if (location <= 0)
    {
        if (csstrcasecmp(path, "Documents\\Halo") == 0)
            strcpy(full_path, ".\\");
        
        strcat(full_path, path);
    }
    else
    {
        strcpy(full_path, "?:\\");
        strncat(full_path, path, MAXIMUM_FILENAME_LENGTH - 4);
    }

#else
#error unsupported platform
#endif
}

bool file_read_only(struct file_reference *file);

void file_error(const char *function_name, const struct file_reference *file);
