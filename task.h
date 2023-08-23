#pragma once

#include "continuation.h"



typedef int task_priority_t;

typedef enum task_state_e
{
    TASK_INIT,
    TASK_ACTIVE,
    TASK_WAITING,
    TASK_YIELDED,
    TASK_EXITED,
} task_state_e;

typedef void * task_parameter_t;

typedef struct task_t
{
    continuation_marker_t   marker;
    const char * name;
    task_priority_t priority;
    task_state_e (*entry)(struct task_t *);
    task_parameter_t parameter;
    task_state_e state;
} task_t;


#define task_init(task, Name, Priority, Entry, Parameter)   \
    do{                                             \
        coninuation_init((task)->marker);           \
        (task)->name = Name;                        \
        (task)->priority = Priority;                \
        (task)->entry = Entry;                      \
        (task)->parameter = Parameter;              \
        (task)->state = TASK_INIT;                  \
    }while(0)


#define task_create(pTask, Name, Priority, Entry, Parameter)    \
    do{                                                         \
        pTask = malloc(sizeof(task_t));                         \
        task_init(pTask, Name, Priority, Entry, Parameter);     \
    }while(0)


#define task_delete(...)  \
    FL_FOREACH(;, free, , __VA_ARGS__)


#define task_entry(entry_name)           \
    task_state_e entry_name(struct task_t *task)


#define task_begin()                            \
        (task)->state = TASK_ACTIVE;                \
        continuation_resume((task)->marker)         \


#define task_exit()                              \
    do{                                         \
        continuation_end();                             \
        coninuation_init((task)->marker);                 \
        (task)->state = TASK_EXITED;                         \
        return TASK_EXITED;                                 \
    }while(0)


#define task_wait_until(condition)            \
    do{                                             \
        continuation_mark((task)->marker);            \
        if(!(condition))                            \
            return (task)->state = TASK_WAITING;      \
    }while(0)


#define task_wait_while(condition)            \
    do{                                             \
        continuation_mark((task)->marker);            \
        if((condition))                            \
            return (task)->state = TASK_WAITING;      \
    }while(0)


#define task_yield()                            \
    do{                                             \
        (task)->state = TASK_YIELDED;               \
        continuation_mark((task)->marker);          \
        if((task)->state == TASK_YIELDED)           \
            return TASK_YIELDED;                    \
    }while(0)


#define task_yield_until(condition)           \
    do{                                             \
        (task)->state = TASK_YIELDED;               \
        continuation_mark((task)->marker);          \
        if((task)->state == TASK_YIELDED            \
        or ! (condition))                           \
            return TASK_YIELDED;                    \
    }while(0)


#define task_schedule(pTask)                        \
    ((pTask)->state < TASK_EXITED ? (pTask)->entry(pTask) < TASK_EXITED : 0)


#define task_join(...)  \
    task_wait_while(FL_FOREACH(|,task_schedule,, __VA_ARGS__))
