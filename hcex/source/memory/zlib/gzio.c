#include "projects/code/hcex/sources/memory/sl_list.h"
#include "projects/code/hcex/sources/memory/texture_page.h"
#include "projects/code/hcex/sources/cseries/cseries.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/stdio.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/time.inl"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/pshpack4.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/poppack.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/stdarg.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/basetsd.h"
#include "projects/code/hcex/sources/memory/circular_queue.h"
#include "projects/code/hcex/sources/math/integer_math.h"
#include "projects/code/hcex/sources/memory/lrar_cache.h"
#include "projects/code/hcex/sources/memory/hashtable.h"
#include "projects/code/hcex/sources/memory/byte_swapping.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/pshpack8.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/stdlib.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/limits.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/winbase.h"
#include "projects/code/hcex/sources/memory/data_packets.h"
#include "projects/code/hcex/sources/cseries/progress.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/guiddef.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/stddef.h"
#include "projects/code/hcex/sources/memory/crc.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/math.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/pshpack2.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/string.h"
#include "projects/code/hcex/sources/math/real_math.h"
#include "projects/code/hcex/sources/bitmaps/bitmaps.h"
#include "projects/code/hcex/sources/memory/data_encoding.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/float.h"
#include "projects/code/hcex/sources/tag_files/files.h"
#include "projects/code/hcex/sources/memory/array.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/crtwrn.h"
#include "projects/code/hcex/sources/cseries/platform.h"
#include "projects/code/hcex/sources/bitmaps/bitmap_group.h"
#include "projects/code/hcex/sources/cseries/cseries_windows.h"
#include "projects/code/hcex/sources/tag_files/tag_groups.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/xdk.h"
#include "projects/code/hcex/sources/tag_files/tag_files.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/windef.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/vadefs.h"
#include "projects/code/hcex/sources/memory/zlib/zutil.h"
#include "projects/code/hcex/sources/cache/cache_files.h"
#include "projects/code/hcex/sources/memory/zlib/zlib.h"
#include "projects/code/hcex/sources/memory/zlib/zconf.h"
#include "projects/code/hcex/sources/memory/lru_cache.h"
#include "projects/code/hcex/sources/cseries/errors.h"
#include "projects/code/hcex/sources/memory/data.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/winerror.h"
#include "projects/code/hcex/sources/math/geometry.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/errno.h"
#include "projects/code/hcex/sources/bitmaps/bitmap_drawing.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/swprintf.inl"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/winnt.h"
#include "projects/code/hcex/sources/memory/lra_cache.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/ctype.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/malloc.h"
#include "projects/code/hcex/sources/halo_defines.h"
#include "projects/code/hcex/sources/cseries/headers.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/time.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/crtdefs.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/sal.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/codeanalysis/sourceannotations.h"
#include "projects/code/hcex/sources/math/periodic_functions.h"
#include "program files (x86)/microsoft xbox 360 sdk/include/xbox/wtime.inl"

int32_t gz_magic[2]; // 0x841ECDD0
typedef z_stream_s * z_streamp;
typedef z_stream_s z_stream;
typedef long time_t;
void * gz_open(const char * path, const char * mode, int32_t fd)// 0x837B0560
{
$M15275:
    const char * path; // r4
    const char * mode; // r5
    int32_t fd; // r6
    char fmode[80]; // r2 offset 112
}
void * gzopen(const char * path, const char * mode)// 0x837B0880
{
    const char * path; // r4
    const char * mode; // r5
}
void * gzdopen(int32_t fd, const char * mode)// 0x837B0888
{
$M15283:
    int32_t fd; // r4
    const char * mode; // r5
    char name[20]; // r2 offset 80
}
int32_t gzsetparams(void * file, int32_t level, int32_t strategy)// 0x837AFA00
{
$M15108:
    void * file; // r4
    int32_t level; // r5
    int32_t strategy; // r6
}
int32_t get_byte(gz_stream * s)// 0x837AFA90
{
$M15114:
    gz_stream * s; // r4
}
void check_header(gz_stream * s)// 0x837AFB58
{
$M15130:
    gz_stream * s; // r4
}
int32_t destroy(gz_stream * s)// 0x837AFD18
{
$M15137:
    gz_stream * s; // r4
}
int32_t gzread(void * file, void * buf, uint32_t len)// 0x837B08F0
{
$M15299:
    void * file; // r4
    void * buf; // r5
    uint32_t len; // r6
}
int32_t gzgetc(void * file)// 0x837B0B80
{
$M15307:
    void * file; // r4
    unsigned char c; // r2 offset 80
}
char * gzgets(void * file, char * buf, int32_t len)// 0x837B0BB8
{
$M15357:
    void * file; // r4
    char * buf; // r5
    int32_t len; // r6
}
int32_t gzwrite(void * file, void * buf, uint32_t len)// 0x837AFE20
{
$M15148:
    void * file; // r4
    void * buf; // r5
    uint32_t len; // r6
}
int32_t gzprintf(void * file, const char * format, ...)// 0x837AFEF0
{
$M15155:
    void * file; // r4
    const char * format; // r5
    char buf[4096]; // r2 offset 96
    char * va; // r2 offset 80
}
int32_t gzputc(void * file, int32_t c)// 0x837AFFA0
{
$M15163:
    void * file; // r4
    int32_t c; // r5
    unsigned char cc; // r2 offset 80
}
int32_t gzputs(void * file, const char * s)// 0x837AFFE0
{
    void * file; // r4
    const char * s; // r5
}
int32_t do_flush(void * file, int32_t flush)// 0x837B0008
{
$M15182:
    void * file; // r4
    int32_t flush; // r5
}
int32_t gzflush(void * file, int32_t flush)// 0x837B0118
{
$M15190:
    void * file; // r4
    int32_t flush; // r5
}
long gzseek(void * file, long offset, int32_t whence)// 0x837B0E80
{
$M15371:
    void * file; // r4
    long offset; // r5
    int32_t whence; // r6
}
int32_t gzrewind(void * file)// 0x837B0168
{
$M15196:
    void * file; // r4
}
long gztell(void * file)// 0x837B1058
{
    void * file; // r4
}
int32_t gzeof(void * file)// 0x837B0230
{
    void * file; // r4
}
void putLong(_iobuf * file, unsigned long x)// 0x837B0258
{
$M15208:
    _iobuf * file; // r4
    unsigned long x; // r5
}
unsigned long getLong(gz_stream * s)// 0x837B0290
{
$M15215:
    gz_stream * s; // r4
}
int32_t gzclose(void * file)// 0x837B0308
{
$M15243:
    void * file; // r4
}
const char * gzerror(void * file, int32_t * errnum)// 0x837B03A8
{
$M15260:
    void * file; // r4
    int32_t * errnum; // r5
}