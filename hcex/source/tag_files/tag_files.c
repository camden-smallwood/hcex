#include "cseries/cseries.h"
#include "tag_files/tag_files.h"

#include <string.h>

/* ---------- public code */

const char *tag_name_strip_path(
    const char *name)
{
    char *s = strrchr(name, '\\');
    return s ? s + 1 : name;
}
