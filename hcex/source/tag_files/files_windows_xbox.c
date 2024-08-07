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

/* ---------- private constants */

enum
{
    FIRST_DRIVE_LETTER = 'A',
    LAST_DRIVE_LETTER = 'Z',
    DRIVE_NAME_LENGTH = 4,
    DIRECTORY_SEPARATOR = '\\',
    EXTENSION_SEPARATOR = '.',
    BAD_FILE = NONE,
    MAXIMUM_SEARCH_DEPTH = 8,
};

/* ---------- private variables */

#if defined(PLATFORM_WINDOWS)
char file_last_cd_drive_name[DRIVE_NAME_LENGTH];
#endif

struct find_files_state
{
    unsigned int flags;
    short depth;
    short location;
    char path[MAXIMUM_FILENAME_LENGTH + 1];

#if defined(PLATFORM_WINDOWS)
    HANDLE handles[MAXIMUM_SEARCH_DEPTH];
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
            __FUNCTION__,
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

    LARGE_INTEGER distance = { .QuadPart = (LONGLONG)position };

    if (SetFilePointerEx(file->handle, distance, NULL, FILE_BEGIN))
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

uint64_t file_get_eof(
    const struct file_reference *file)
{
    file_reference_verify(file);

#if defined(PLATFORM_WINDOWS)

    LARGE_INTEGER result;

    if (GetFileSizeEx(file->handle, &result))
        return (uint64_t)result.QuadPart;

#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)

    struct stat buf;

    if (fstat(file->fd, &buf) >= 0)
        return (uint64_t)buf.st_size;

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

    return 0;
}

bool file_set_eof(
    const struct file_reference *file,
    uint64_t position)
{
    file_reference_verify(file);

    if (!file_set_position(file, position))
        return false;

#if defined(PLATFORM_WINDOW)
    
    if (SetEndOfFile(file->handle))
        return true;
    
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)

    if (ftruncate(file->fd, (off_t)position) >= 0)
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

bool file_read(
    const struct file_reference *file,
    size_t count,
    void *buffer)
{
    file_reference_verify(file);
    assert(buffer);

    for (;;)
    {
#if defined(PLATFORM_WINDOWS)
        DWORD bytes_read = 0;

        if (!ReadFile(file->handle, buffer, count, &bytes_read, NULL))
            break;
        
        if (bytes_read == 0)
        {
            SetLastError(ERROR_HANDLE_EOF);
            break;
        }
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
        ssize_t bytes_read = read(file->fd, buffer, count);

        if (bytes_read < 0)
            break;
#else
#error unsupported platform
#endif

        count -= (size_t)bytes_read;
        buffer = (char *)buffer + bytes_read;

        if (count == 0)
            return true;
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

bool file_write(
    const struct file_reference *file,
    size_t count,
    const void *buffer)
{
    file_reference_verify(file);
    assert(buffer);

    for (;;)
    {
#if defined(PLATFORM_WINDOWS)
        DWORD bytes_written = 0;

        if (!WriteFile(file->handle, buffer, count, &bytes_written, NULL))
            break;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
        ssize_t bytes_written = write(file->fd, buffer, count);

        if (bytes_written < 0)
            break;
#else
#error unsupported platform
#endif

        count -= (size_t)bytes_written;
        buffer = (char *)buffer + bytes_written;

        if (count == 0)
            return true;
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

bool file_read_from_position(
    const struct file_reference *file,
    uint64_t position,
    size_t count,
    void *buffer)
{
    return file_set_position(file, position)
        && file_read(file, count, buffer);
}

bool file_write_to_position(
    const struct file_reference *file,
    uint64_t position,
    size_t count,
    const void *buffer)
{
    return file_set_position(file, position)
        && file_write(file, count, buffer);
}

bool file_get_last_modification_date(
    const struct file_reference *file,
    struct file_last_modification_date *date)
{
    file_reference_verify(file);

    char full_path[MAXIMUM_FILENAME_LENGTH];
    memset(full_path, 0, sizeof(full_path));

    memset(date, 0, sizeof(*date));

    file_location_get_full_path(file->location, (char *)file->path, full_path);

#if defined(PLATFORM_WINDOWS)
    WIN32_FILE_ATTRIBUTE_DATA file_attributes;

    if (GetFileAttributesExA(full_path, GetFileExInfoStandard, &file_attributes))
    {
        memcpy(&date->filetime, &file_attributes.ftLastWriteTime, sizeof(date->filetime));
        return true;
    }
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
    struct stat buf;

    if (stat(full_path, &buf) == 0)
    {
        memcpy(&date->timespec, &buf.st_mtimespec, sizeof(date->timespec));
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

int file_compare_last_modification_dates(
    struct file_last_modification_date *date1,
    struct file_last_modification_date *date2)
{
    return memcmp(date1, date2, sizeof(*date1));
}

bool file_get_size(
    const struct file_reference *file,
    uint64_t *size)
{
    file_reference_verify(file);
    assert(size);
    
    char full_path[MAXIMUM_FILENAME_LENGTH];
    memset(full_path, 0, sizeof(full_path));
    
    file_location_get_full_path(file->location, (char *)file->path, full_path);

#if defined(PLATFORM_WINDOWS)
    WIN32_FILE_ATTRIBUTE_DATA file_attributes;

    if (GetFileAttributesExA(full_path, GetFileExInfoStandard, &file_attributes))
    {
        #warning TODO: check nFileSizeHigh
        *size = (uint64_t)file_attributes.nFileSizeLow;
        return true;
    }
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
    struct stat buf;

    if (stat(full_path, &buf) == 0)
    {
        *size = (uint64_t)buf.st_size;
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

void find_files_start(
    unsigned int flags,
    const struct file_reference *directory)
{
    file_reference_verify(directory);
    assert(VALID_FLAGS(flags, NUMBER_OF_FIND_FILES_FLAGS));
    assert(!TEST_FLAG(directory->flags, _has_filename_bit));

#if defined(PLATFORM_WINDOWS)
    for (int i = find_files_globals.depth; i >= 0; i--)
    {
        HANDLE *handle = &find_files_globals.handles[i];

        if (*handle != INVALID_HANDLE)
        {
            CloseHandle(*handle);
            *handle = INVALID_HANDLE;
        }
    }
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
#error TODO
#else
#error unsupported platform
#endif
    
    find_files_globals.flags = flags;
    find_files_globals.depth = 0;
    find_files_globals.location = directory->location;

    strcpy(find_files_globals.path, directory->path);
}

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
