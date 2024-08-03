#pragma once

/* ---------- constants */

enum /* thread attribute flags */
{
    _thread_attribute_flag_default,
    _thread_attribute_flag_priority_low,
    _thread_attribute_flag_priority_high,
    NUMBER_OF_THREAD_ATTRIBUTE_FLAGS
};

enum
{
    MUTEX_NAME_LENGTH = 32,
    THREAD_STACK_SIZE = 0x4000,
};

/* ---------- structures */

struct thread
{
    void *object;
    bool in_use;
};

struct mutex
{
    void *object;
    char name[MUTEX_NAME_LENGTH];
    bool in_use;
};

/* ---------- types */

typedef struct thread *thread_ref;
typedef uint32_t (*thread_function)(void *);
typedef struct mutex *mutex_ref;

/* ---------- prototypes/THREAD_WIN32.C */

struct thread *get_thread_from_pool(void);
struct mutex *get_mutex_from_pool(void);

bool create_thread(uint16_t flags, thread_function function, void *function_input, struct thread **thread_reference);
bool thread_has_exited(struct thread *thread_reference);
void dispose_thread(struct thread *thread_reference);

bool create_mutex(struct mutex **mutex_reference);
bool take_mutex(struct mutex *mutex_reference, uint32_t milliseconds_to_wait);
void release_mutex(struct mutex *mutex_reference);
void dispose_mutex(struct mutex *mutex_reference);
