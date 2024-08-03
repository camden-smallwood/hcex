#include "cseries/cseries.h"
#include "bungie_net/common/thread.h"

uint32_t mutex_count;
struct thread thread_pool[32];
struct mutex mutex_pool[32];

struct thread *get_thread_from_pool(
    void);

struct mutex *get_mutex_from_pool(
    void);

bool create_thread(
    uint16_t flags,
    thread_function function,
    void *function_input,
    struct thread **thread_reference)
{
    uint32_t unused_thread_id; // r2 offset 80
}

bool thread_has_exited(
    struct thread *thread_reference)
{
    uint32_t exit_code; // r2 offset 80
}

void dispose_thread(
    struct thread *thread_reference);

bool create_mutex(
    struct mutex **mutex_reference);

bool take_mutex(
    struct mutex *mutex_reference,
    uint32_t milliseconds_to_wait);

void release_mutex(
    struct mutex *mutex_reference);

void dispose_mutex(
    struct mutex *mutex_reference);
