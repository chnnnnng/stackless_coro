#pragma once

#include "continuation.h"

#include "stdint.h"
#include "stdlib.h"

typedef uint8_t task_priority_t;

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
    uint8_t malloc_flag;
    task_state_e (*entry)(struct task_t *);
    task_parameter_t parameter;
    task_state_e state;
    struct task_t * next;
    struct task_t * prev;
    struct task_lists_t * list;
} task_t;


#define task_create_static(pTask, Name, Priority, Entry, Parameter)   \
    do{                                             \
        coninuation_init((pTask)->marker);           \
        (pTask)->name = Name;                        \
        (pTask)->priority = Priority;                \
        (pTask)->malloc_flag = 0;                    \
        (pTask)->entry = Entry;                      \
        (pTask)->parameter = Parameter;              \
        (pTask)->state = TASK_INIT;                  \
        task_list_push((pTask));                    \
    }while(0)


#define task_create(pTask, Name, Priority, Entry, Parameter)    \
    do{                                                         \
        pTask = malloc(sizeof(task_t));                         \
        task_create_static(pTask, Name, Priority, Entry, Parameter);     \
        (pTask)->malloc_flag = 1;                               \
    }while(0)


#define _task_delete(pTask) \
    do{                             \
        task_list_del(pTask);       \
        if(pTask->malloc_flag)      \
            free(pTask);            \
    }while(0)


#define task_delete(...)  \
    FL_FOREACH(;, _task_delete, , __VA_ARGS__)


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



#define task_wait_while(condition)            \
    do{                                             \
        continuation_mark((task)->marker);            \
        if((condition))                            \
            return (task)->state = TASK_WAITING;      \
    }while(0)


#define task_wait_until(condition)            \
    task_wait_while(!(condition))


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


#define _task_is_exited(pTask)                      \
    ((pTask)->state < TASK_EXITED ? 1 : 0)

#define task_join(...)  \
    task_wait_while(FL_FOREACH(|,_task_is_exited,, __VA_ARGS__))


#define task_start_scheduler()                                                  \
    do{                                                                         \
        task_t * task_to_schedule;                                              \
        /*从任务队列中取出最优先调度的任务*/                                       \
        while((task_to_schedule = task_list_pop()))                             \
        {                                                                       \
            /*调度该任务*/                                                       \
            if(task_schedule(task_to_schedule))                                 \
            {                                                                   \
                /*如果返回值为1，表示此次调度结束，即该任务主动yield或者wait*/      \
            }                                                                   \
            else                                                                \
            {                                                                   \
                /*如果返回值为0，表示任务已结束，则删除之*/                        \
                task_delete(task_to_schedule);                                  \
            }                                                                   \
            /*如除了本调度器外，还有其他的线程需要执行，应在此出让CPU时间*/          \
            task_scheduler_spare_time();                                        \
        }                                                                       \
    }while(0)                                                          