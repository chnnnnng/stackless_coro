#pragma once

#include "common.h"
#include "continuation.h"
#include "timer.h"
#include "memory.h"

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

typedef struct task_flag_t
{
    uint8_t malloc     : 1;
    uint8_t sleeping   : 1;
    uint8_t timeout    : 1;
} task_flag_t;

typedef struct task_t
{
    continuation_marker_t   marker;
    const char * name;
    task_priority_t priority;
    task_flag_t flags;
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
        (pTask)->flags.malloc = 0;                   \
        (pTask)->flags.sleeping = 0;                 \
        (pTask)->flags.timeout = 0;                   \
        (pTask)->entry = Entry;                      \
        (pTask)->parameter = Parameter;              \
        (pTask)->state = TASK_INIT;                  \
        _task_list_push((pTask));                    \
    }while(0)


#define task_create(pTask, Name, Priority, Entry, Parameter)    \
    do{                                                         \
        pTask = mem_alloc(sizeof(task_t));                         \
        task_create_static(pTask, Name, Priority, Entry, Parameter);     \
        (pTask)->flags.malloc = 1;                               \
    }while(0)


#define _task_delete(pTask) \
    do{                             \
        _task_list_del(pTask);       \
        if(pTask->flags.malloc)      \
            mem_free(pTask);            \
    }while(0)


#define task_delete(...)  \
    FL_FOREACH(;, _task_delete, , __VA_ARGS__)


#define task_entry(entry_name)           \
    task_state_e entry_name(struct task_t *task)


#define task_begin()                            \
        (task)->state = TASK_ACTIVE;                \
        static retval ret = RET_OK;                 \
        static timer_handler timer;                 \
        continuation_resume((task)->marker)         \


#define task_exit()                              \
    do{                                         \
        continuation_end();                             \
        coninuation_init((task)->marker);                 \
        (task)->state = TASK_EXITED;                         \
        return TASK_EXITED;                                 \
    }while(0)


#define task_yield()                            \
    do{                                             \
        (task)->state = TASK_YIELDED;               \
        continuation_mark((task)->marker);          \
        if((task)->state == TASK_YIELDED)           \
            return TASK_YIELDED;                    \
    }while(0)


#define task_wait_while(condition)            \
    do{                                             \
        continuation_mark((task)->marker);            \
        if((condition))                            \
            return (task)->state = TASK_WAITING;      \
    }while(0)


#define task_wait_until(condition)            \
    task_wait_while(!(condition))


#define task_wait_while_timeout(condition, Timeout)            \
    do{                                             \
        timer = _task_set_timeout_timer((task), ((ltime_t)(Timeout)));    \
        continuation_mark((task)->marker);            \
        if((condition) && ((task)->flags.timeout == 0)) \
            return (task)->state = TASK_WAITING;      \
        else if((task)->flags.timeout == 0)         \
        {                                            \
            timer_unset(timer);                         \
            ret = RET_OK;                            \
        }                                           \
        else                                        \
        {                                           \
            ret = RET_TO;                           \
        }                                           \
    }while(0)


#define task_wait_until_timeout(condition, Timeout)            \
    task_wait_while_timeout((!(condition)), (Timeout))


#define task_schedule(pTask)                        \
    ((pTask)->state < TASK_EXITED ? (pTask)->entry(pTask) < TASK_EXITED : 0)


#define _task_is_exited(pTask)                      \
    ((pTask)->state < TASK_EXITED ? 1 : 0)


#define task_join(...)  \
    task_wait_while(FL_FOREACH(|,_task_is_exited,, __VA_ARGS__))


#define task_sleep(time_in_tick)                    \
    do{                                             \
        _task_set_sleep_timer((task), ((ltime_t)time_in_tick));\
        task_wait_while((task)->flags.sleeping == 1);   \
    }while(0)


#define task_start_scheduler()                                                  \
    do{                                                                         \
        task_t * task_to_schedule;                                              \
        /*从任务队列中取出最优先调度的任务*/                                       \
        while((task_to_schedule = _task_list_pop()))                             \
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
