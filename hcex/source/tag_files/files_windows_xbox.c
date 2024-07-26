#include "cseries/cseries.h"
#include "tag_files/files.h"

#if defined(PLATFORM_WINDOWS)
#   define WIN32_LEAN_AND_MEAN
#   include <Windows.h>
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
#   include <sys/stat.h>
#   include <fcntl.h>
#   include <ftw.h>
#   include <unistd.h>
#else
#   error unsupported platform
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
    _WIN32_FIND_DATAA data;
#endif
} find_files_globals;

/* ---------- private prototypes */

#if defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
static int rmdir_recursive(const char *file_name, const struct stat *sbuf, int type, struct FTW *ftwb);
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
    #   warning TODO: finish refactoring
        HANDLE handle = CreateFileA(file_name, 0x40000000, 0, 0, 2, 0x80, 0);
        if (handle != (HANDLE)NONE)
        {
            CloseHandle(handle);
            return true;
        }
    #elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
        if (mknod(file_name, S_IFREG | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH, 0) >= 0)
            return true;
    #else
    #   error unsupported platform
    #endif
    }
    else
    {
    #if defined(PLATFORM_WINDOWS)
    #   warning TODO: finish refactoring
        if (CreateDirectoryA(file->path, 0))
            return true;
    #elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
        if (mkdir(file_name, S_IRWXU | S_IRWXG | S_IRWXO) >= 0)
            return true;
    #else
    #   error unsupported platform
    #endif
    }

#if defined(PLATFORM_WINDOWS)
#   warning TODO: finish refactoring
    error(2, "%s('%s') error 0x%08x", "file_create", file->path, GetLastError());
    SetLastError(0);
#else
#   warning TODO: handle error here
#endif

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
    #   warning TODO: finish refactoring
        if (SetFileAttributesA(file_name, 0x80u) && DeleteFileA(file_name))
            return true;
    #elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
        if (remove(file_name) >= 0)
            return true;
    #else
    #   error unsupported platform
    #endif
    }
    else
    {
    #if defined(PLATFORM_WINDOWS)
    #   warning TODO: finish refactoring
        if (RemoveDirectoryA(file_name))
            return true;
    #elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
        if (nftw(file_name, rmdir_recursive, OPEN_MAX, FTW_DEPTH | FTW_MOUNT | FTW_PHYS) >= 0)
            return true;
    #else
    #   error unsupported platform
    #endif
    }

#if defined(PLATFORM_WINDOWS)
#   warning TODO: finish refactoring
    error(2, "%s('%s') error 0x%08x", "file_delete", file->path, GetLastError());
    SetLastError(0);
#else
#   warning TODO: handle error here
#endif

    return false;
}

bool file_exists(
    const struct file_reference *file)
{
    file_reference_verify((struct file_reference *)file);

    char file_name[MAXIMUM_FILENAME_LENGTH];
    memset(file_name, 0, sizeof(file_name));

    file_location_get_full_path(file->location, (char *)file->path, file_name);

#if defined(PLATFORM_WINDOWS)
#   warning TODO: finish refactoring
    if (GetFileAttributesA(file_name) != -1)
        return true;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
    struct stat buffer;
    if (stat(file_name, &buffer) == 0)
        return true;
#else
#   error unsupported platform
#endif

#if defined(PLATFORM_WINDOWS)
#   warning TODO: finish refactoring
    if (GetLastError() != 2 && GetLastError() != 3)
        file_error("file_exists");
#else
#   warning TODO: handle error here
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
#   warning TODO: finish refactoring
    if (!MoveFileA(&full_path, &v8))
        return false;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
    if (rename(old_full_path, new_full_path) < 0)
        return false;
#else
#   error unsupported platform
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
#   warning TODO: finish refactoring

    unsigned int create_file_flags = 0x80000000;

    if (read)
        create_file_flags = 0;

    if (write)
        create_file_flags |= 0x40000000u;

    HANDLE handle = CreateFileA(full_path, create_file_flags, 0, 0, 3u, 0x80u, 0);

    if (handle == INVALID_HANDLE_VALUE)
    {
        LastError = GetLastError();
        error(2, "%s('%s') error 0x%08x", "file_open", file->path, LastError);
        SetLastError(0);
        return false;
    }

    file->handle = handle;

    if (!append)
        return true;

    if (SetFilePointer(handle, 0, 0, 2u) == -1)
    {
        CloseHandle((HANDLE)file[1].signature);
        file[1].signature = 0;
        LastError = GetLastError();
        error(2, "%s('%s') error 0x%08x", "file_open", file->path, LastError);
        SetLastError(0);
        return false;
    }

#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
#   warning TODO: handle errors

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
#   error unsupported platform
#endif

    return true;
}

bool file_close(
    struct file_reference *file)
{
    file_reference_verify(file);

#if defined(PLATFORM_WINDOWS)
#   warning TODO: finish refactoring
    if (CloseHandle((HANDLE)file[1].signature))
    {
        file[1].signature = 0;
        return 1;
    }
    else
    {
        v3 = file_reference_verify(file);
        LastError = GetLastError();
        error(2, "%s('%s') error 0x%08x", "file_close", v3->path, LastError);
        SetLastError(0);
        return 0;
    }
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
#   warning TODO: handle errors
    close(file->fd);
#else
#   error unsupported platform
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

bool file_read_only(struct file_reference *file);

void file_error(const char *function_name, const struct file_reference *file);

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
