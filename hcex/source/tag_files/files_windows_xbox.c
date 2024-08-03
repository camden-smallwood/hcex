#include "cseries/cseries.h"
#include "cseries/errors.h"
#include "tag_files/files.h"

#if defined(PLATFORM_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ftw.h>
#include <unistd.h>
#else
#error unsupported platform
#endif

#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* ---------- private variables */

#if defined(PLATFORM_WINDOWS)
char file_last_cd_drive_name[4];
#endif

struct find_files_state
{
    unsigned int flags;
    short depth;
    short location;
    char path[MAXIMUM_FILENAME_LENGTH + 1];
    void *handles[8];

#if defined(PLATFORM_WINDOWS)
    WIN32_FIND_DATAA data;
#endif
} find_files_globals;

/* ---------- private prototypes */

#if defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
static int rmdir_recursive(
    const char *file_name,
    const struct stat *sbuf,
    int type,
    struct FTW *ftwb);
#endif

/* ---------- public code */

bool file_create(
    struct file_reference *file)
{
    file_reference_verify(file);

    char file_name[MAXIMUM_FILENAME_LENGTH];
    memset(file_name, 0, sizeof(file_name));

    file_location_get_full_path(file->location, file->path, file_name);

    if (TEST_FLAG(file->flags, _has_filename_bit))
    {
#if defined(PLATFORM_WINDOWS)
        HANDLE handle = CreateFileA(file_name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        if (handle != INVALID_HANDLE_VALUE)
        {
            CloseHandle(handle);
            return true;
        }
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
        if (mknod(file_name, S_IFREG | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH, 0) >= 0)
            return true;
#else
#error unsupported platform
#endif
    }
    else
    {
#if defined(PLATFORM_WINDOWS)
        if (CreateDirectoryA(file->path, NULL))
            return true;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
        if (mkdir(file_name, S_IRWXU | S_IRWXG | S_IRWXO) >= 0)
            return true;
#else
#error unsupported platform
#endif
    }

    error(
        _error_message_priority_assert,
        "%s('%s') error 0x%08x",
        __FUNCTION__,
        file->path,
        system_get_error_code());

    system_set_error_code(0);

    return false;
}

bool file_delete(
    struct file_reference *file)
{
    file_reference_verify(file);

    char file_name[MAXIMUM_FILENAME_LENGTH];
    memset(file_name, 0, sizeof(file_name));

    file_location_get_full_path(file->location, file->path, file_name);

    if (TEST_FLAG(file->flags, _has_filename_bit))
    {
#if defined(PLATFORM_WINDOWS)
#warning TODO: finish refactoring
        if (SetFileAttributesA(file_name, 0x80u) && DeleteFileA(file_name))
            return true;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
        if (remove(file_name) >= 0)
            return true;
#else
#error unsupported platform
#endif
    }
    else
    {
#if defined(PLATFORM_WINDOWS)
#warning TODO: finish refactoring
        if (RemoveDirectoryA(file_name))
            return true;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
        if (nftw(file_name, rmdir_recursive, OPEN_MAX, FTW_DEPTH | FTW_MOUNT | FTW_PHYS) >= 0)
            return true;
#else
#error unsupported platform
#endif
    }

    error(
        _error_message_priority_assert,
        "%s('%s') error 0x%08x",
        __FUNCTION__,
        file->path,
        system_get_error_code());

    system_set_error_code(0);

    return false;
}

bool file_exists(
    const struct file_reference *file)
{
    file_reference_verify(file);

    char file_name[MAXIMUM_FILENAME_LENGTH];
    memset(file_name, 0, sizeof(file_name));

    file_location_get_full_path(file->location, (char *)file->path, file_name);

#if defined(PLATFORM_WINDOWS)

    if (GetFileAttributesA(file_name) != INVALID_FILE_ATTRIBUTES)
        return true;

#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)

    struct stat buffer;

    if (stat(file_name, &buffer) == 0)
        return true;

#else
#error unsupported platform
#endif

#if defined(PLATFORM_WINDOWS)
#warning TODO: finish refactoring
    if (GetLastError() != 2 && GetLastError() != 3)
        file_error(__FUNCTION__, file);
#else
#warning TODO: handle errors
#endif

    return false;
}

bool file_rename(
    struct file_reference *file,
    const char *name)
{
    file_reference_verify(file);

    char old_full_path[MAXIMUM_FILENAME_LENGTH];
    memset(old_full_path, 0, sizeof(old_full_path));

    char new_full_path[MAXIMUM_FILENAME_LENGTH];
    memset(new_full_path, 0, sizeof(new_full_path));

    file_location_get_full_path(file->location, file->path, old_full_path);

    strcpy(new_full_path, old_full_path);

    file_path_remove_name(new_full_path);
    file_path_add_name(new_full_path, name);

#if defined(PLATFORM_WINDOWS)
    if (!MoveFileA(old_full_path, new_full_path))
        return false;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
    if (rename(old_full_path, new_full_path) < 0)
        return false;
#else
#error unsupported platform
#endif

    file_path_remove_name(file->path);
    file_path_add_name(file->path, name);

    return true;
}

bool file_open(
    struct file_reference *file,
    unsigned int flags)
{
    file_reference_verify(file);

    assert(VALID_FLAGS(flags, NUMBER_OF_PERMISSION_FLAGS));

    bool read = TEST_FLAG(flags, _permission_read_bit);
    bool write = TEST_FLAG(flags, _permission_write_bit);
    bool append = TEST_FLAG(flags, _permission_append_bit);

    assert(read || write);
    assert(write || !append);

    char full_path[MAXIMUM_FILENAME_LENGTH];
    memset(full_path, 0, sizeof(full_path));

    file_location_get_full_path(file->location, file->path, full_path);

#if defined(PLATFORM_WINDOWS)
#warning TODO: finish refactoring

    unsigned int access_flags = 0;

    if (read)
        access_flags = GENERIC_READ;

    if (write)
        access_flags |= GENERIC_WRITE;

    HANDLE handle = CreateFileA(full_path, access_flags, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (handle == INVALID_HANDLE_VALUE)
    {
        error(
            _error_message_priority_assert,
            "%s('%s') error 0x%08x",
            "file_open",
            file->path,
            GetLastError());

        SetLastError(0);

        return false;
    }

    file->handle = handle;

    if (!append)
        return true;

    if (SetFilePointer(handle, 0, 0, 2u) == INVALID_SET_FILE_POINTER)
    {
        CloseHandle(file->handle);
        file->handle = NULL;

        error(
            _error_message_priority_assert,
            "%s('%s') error 0x%08x",
            "file_open",
            file->path,
            GetLastError());

        SetLastError(0);

        return false;
    }

#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
#warning TODO: handle errors

    int open_flags = 0;
    mode_t open_mode = 0;

    if (read && write)
    {
        open_flags = O_RDWR;
        open_mode = S_IRUSR | S_IWUSR;
    }
    else if (read)
    {
        assert(!append);
        open_flags = O_RDONLY;
        open_mode = S_IRUSR;
    }
    else if (write)
    {
        open_flags = O_WRONLY;
        open_mode = S_IWUSR;
    }

    if (append)
        open_flags |= O_APPEND;

    int fd = open(full_path, open_flags, open_mode);

    if (fd < 0)
        return false;

    file->fd = fd;

#else
#error unsupported platform
#endif

    return true;
}

bool file_close(
    struct file_reference *file)
{
    file_reference_verify(file);

#if defined(PLATFORM_WINDOWS)
    if (CloseHandle(file->handle))
    {
        file->handle = NULL;
        return true;
    }
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
    if (close(file->fd) >= 0)
    {
        file->fd = NONE;
        return true;
    }
#else
#error unsupported platform
#endif

    error(
        _error_message_priority_assert,
        "%s('%s') error 0x%08x",
        __FUNCTION__,
        file->path,
        system_get_error_code());

    system_set_error_code(0);

    return false;
}

uint64_t file_get_position(
    const struct file_reference *file)
{
    file_reference_verify(file);

#if defined(PLATFORM_WINDOWS)
#warning TODO: finish refactoring

    DWORD v2 = SetFilePointer(file->handle, 0, 0, 1u);

    if (v2 == -1)
    {
        error(
            _error_message_priority_assert,
            "%s('%s') error 0x%08x",
            "file_get_position",
            file->path,
            GetLastError());

        SetLastError(0);
    }

    return v2;

#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)

    off_t result = lseek(file->fd, 0, SEEK_CUR);

    if (result < 0)
    {
#warning TODO: handle errors
        return 0;
    }

    return (uint64_t)result;

#else
#error unsupported platform
#endif
}

bool file_set_position(
    const struct file_reference *file,
    uint64_t position)
{
    file_reference_verify(file);

#if defined(PLATFORM_WINDOWS)
#warning TODO: construct proper `lpDistanceToMoveHigh` if necessary
    if (SetFilePointer(file->handle, position, 0, FILE_BEGIN) != INVALID_SET_FILE_POINTER)
        return true;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
    if (lseek(file->fd, position, SEEK_SET) >= 0)
        return true;
#else
#error unsupported platform
#endif

    error(
        _error_message_priority_assert,
        "%s('%s') error 0x%08x",
        __FUNCTION__,
        file->path,
        system_get_error_code());

    system_set_error_code(0);

    return false;
}

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

#if defined(PLATFORM_WINDOWS)
#warning TODO: finish refactoring

    if (!path[0] || !path[1] || !path[2] || !isalpha(path[0]) || path[1] != ':' || path[2] != '\\')
        strcpy(full_path, "d:\\");

    strcat(full_path, path);

#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
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

bool file_read_only(
    struct file_reference *file);

void file_error(
    const char *function_name,
    const struct file_reference *file);

/* ---------- private code */

#if defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
static int rmdir_recursive(
    const char *file_name,
    const struct stat *sbuf,
    int type,
    struct FTW *ftwb)
{
    if (remove(file_name) >= 0)
        return 0;

    perror("ERROR: Failed to remove file system entry");
    return -1;
}
#endif
