#include "task.h"


typedef struct task_lists_t
{
    uint32_t    bitmap;
    task_t *    lists[32];
} task_lists_t;


static task_lists_t task_list_a = {.bitmap = 0, .lists = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
                    task_list_b = {.bitmap = 0, .lists = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
                    *task_list = &task_list_a,
                    *task_list_the_other = &task_list_b;


static void __task_list_push(task_t ** list, task_t * task_to_push)
{
    if(*list == NULL)
    {
        task_to_push->next = task_to_push;
        task_to_push->prev = task_to_push;
        *list = task_to_push;
    }    
    else
    {
        task_t * head = *list;
        task_t * tail = head->prev;
        tail->next = task_to_push;
        task_to_push->prev = tail;
        task_to_push->next = head;
        head->prev = task_to_push;
    }
}


static task_t * __task_list_pop(task_t ** list)
{
    if(*list == NULL)
    {
        return NULL;
    }
    else
    {
        task_t * head = *list;
        task_t * tail = head->prev;
        task_t * new_head = head->next;
        if(new_head == head)
        {
            *list = NULL;
            return new_head;
        }
        else
        {
            tail->next = new_head;
            new_head->prev = tail;
            *list = new_head;
            return head;
        }
    }
}


static uint8_t _fls(uint32_t x)  
{  
    uint8_t r = 32;  
  
    if (!x)  
        return 0;  
    if (!(x & 0xffff0000u)) {  
        x <<= 16;  
        r -= 16;  
    }  
    if (!(x & 0xff000000u)) {  
        x <<= 8;  
        r -= 8;  
    }  
    if (!(x & 0xf0000000u)) {  
        x <<= 4;  
        r -= 4;  
    }  
    if (!(x & 0xc0000000u)) {  
        x <<= 2;  
        r -= 2;  
    }  
    if (!(x & 0x80000000u)) {  
        x <<= 1;  
        r -= 1;  
    }  
    return r;  
}  


void _task_list_push(task_t * task)
{
    __task_list_push(&(task_list->lists[task->priority]), task);
    task_list->bitmap |= (1 << (task->priority & 31));
    task->list = task_list;
}


task_t * _task_list_pop(void)
{
    uint8_t highest_priority = _fls(task_list->bitmap);
    if(highest_priority == 0)
    {
        return NULL;
    }
    else
    {
        highest_priority -= 1;
        task_t * popped_task = __task_list_pop(&(task_list->lists[highest_priority]));
        __task_list_push(&(task_list_the_other->lists[highest_priority]), popped_task);
        task_list_the_other->bitmap |= (1 << (highest_priority & 31));
        popped_task->list = task_list_the_other;
        if(task_list->lists[highest_priority] == NULL)
        {
            task_list->bitmap &= (~(1 << highest_priority));
        }
        if(task_list->bitmap == 0)
        {
            task_lists_t * temp = task_list;
            task_list = task_list_the_other;
            task_list_the_other = temp;
        }
        return popped_task;
    }
}


void _task_list_del(task_t * task)
{
    task_t * next = task->next;
    task_t * prev = task->prev;
    if(next == prev && prev == task)
    {
        task->list->lists[task->priority] = NULL;
        task->list->bitmap &= (~(1 << task->priority));
        task->list = NULL;
    }
    else
    {
        prev->next = next;
        next->prev = prev;
        task->list = NULL;
    }
}


static void _task_sleep_timer_callback(void * parameter)
{
    task_t * task = (task_t *)parameter;
    task->flags.sleeping = 0;
}


void _task_set_sleep_timer(task_t * task, ltime_t time)
{
    task->flags.sleeping = 1;
    timer_set(time, _task_sleep_timer_callback, task);
}

static void _task_timeout_timer_callback(void * parameter)
{
    task_t * task = (task_t *)parameter;
    task->flags.timeout = 1;
}

timer_handler _task_set_timeout_timer(task_t * task, ltime_t time)
{
    task->flags.timeout = 0;
    return timer_set(time, _task_timeout_timer_callback, task);
}


__attribute__((weak)) void task_scheduler_spare_time(void)
{
    //sleep(1);
}
