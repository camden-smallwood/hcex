#include "cseries/cseries.h"
#include "memory/data.h"
#include "saved games/game_state.h"

int32_t hcex_dont_skip_cine;
<unnamed - tag> game_state_globals;
void (*before_save_procs)()[1];
void (*before_load_procs)()[1];
void (*after_load_procs)()[15];

typedef void (*game_state_before_load_proc)();
typedef void (*game_state_after_load_proc)();
typedef void (*game_state_before_save_proc)();

int32_t get_game_state_header_size(...);
void game_state_initialize(void);
void game_state_dispose(void);
void game_state_initialize_for_new_map(void);
void game_state_dispose_from_old_map(void);
void *game_state_malloc(const char *name, const char *type, long size);
void *game_state_gpu_malloc(const char *name, const char *type, long size);
struct data_array *game_state_data_new(const char *name, short maximum_count, short size);
struct memory_pool *game_state_memory_pool_new(const char *name, long size)
{
$M33420:
    const char *name; // r4
    long size;        // r5
}
lruv_cache *game_state_lruv_cache_new(const char *name, long page_count, long page_size_bits, long maximum_block_count, void (*delete_block_proc)(long), unsigned char (*locked_block_proc)(long))
{
$M33433:
    const char *name;                         // r4
    long page_count;                          // r5
    long page_size_bits;                      // r6
    long maximum_block_count;                 // r7
    void (*delete_block_proc)(long);          // r8
    unsigned char (*locked_block_proc)(long); // r9
}
void game_state_save(unsigned char do_autosave)
{
$M33448:
    unsigned char do_autosave; // r4
}
void hcex_game_state_set_saved_game_valid(int32_t value)
{
    int32_t value; // r4
}
void *game_state_addr(...);
int32_t game_state_size(...);
void *game_state_actors_addr(...);
int32_t game_state_actors_size(...);
void game_state_dump_actors(int32_t idx)
{
$M33464:
    int32_t idx;    // r4
    char fname[64]; // r2 offset 80
}
unsigned long game_state_calculate_crc(...)
{
$M33473:
    data_iterator iterator; // r2 offset 96
    unsigned long crc;      // r2 offset 80
}
void game_state_revert()
{
$M33479:
}
void hcex_game_state_revert(void *data, int32_t data_size)
{
$M33485:
    void *data;        // r4
    int32_t data_size; // r5
}
void game_state_try_and_load_from_persistent_storage()
{
$M33571:
    game_state_header header; // r2 offset 80
}
void game_state_save_to_persistent_storage()
{
$M33491:
}
unsigned char game_state_test_persistent_storage(char *map_name, short *difficulty, unsigned char *corrupted)
{
$M33499:
    char *map_name;           // r4
    short *difficulty;        // r5
    unsigned char *corrupted; // r6
    game_state_header header; // r2 offset 80
}
void game_state_save_core(const char *name)
{
$M33506:
    const char *name; // r4
}
void game_state_load_core(const char *name)
{
$M33577:
    const char *name;         // r4
    game_state_header header; // r2 offset 80
}
unsigned char game_state_reverted()
{
$M33512:
}
unsigned char game_state_header_valid(game_state_header *header, unsigned char)
{
$M33528:
    game_state_header *header; // r4
    unsigned char fatal;       // r2 offset 128
}
unsigned char hcex_verify_savegame(void *data, int32_t data_size)
{
    void *data;        // r4
    int32_t data_size; // r5
}
void game_state_set_revert_time()
{
$M33536:
}
unsigned char hcex_dbg_checkpoint_write(void *buffer, long buffer_size)
{
$M33542:
    void *buffer;     // r4
    long buffer_size; // r5
}
unsigned char hcex_dbg_checkpoint_read_header(const char *filename)
{
$M33548:
    const char *filename;     // r4
    game_state_header header; // r2 offset 80
}
unsigned char hcex_dbg_checkpoint_read(void *buffer, long buffer_size)
{
$M33554:
    void *buffer;     // r4
    long buffer_size; // r5
}
