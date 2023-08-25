#include "timer.h"
#include "memory.h"


typedef struct timer_queue_node_t{
    ltime_t                    time;
    timer_callback              callback;
    timer_parameter             parameter;
    struct timer_queue_node_t   *next;
} timer_queue_node_t;


typedef struct {
    timer_queue_node_t           *head;
    timer_queue_node_t           *tail;
} timer_queue_t;

static timer_queue_t timer_queue = {.head = NULL, .tail = NULL};

static ltime_t local_time = 0;

static timer_handler timer_queue_push(ltime_t time, timer_callback callback, timer_parameter parameter)
{
    timer_queue_node_t *node = mem_alloc(sizeof(timer_queue_node_t));
    if(node)
    {
        node->time = time;
        node->callback = callback;
        node->parameter = parameter;
        node->next = NULL;
       
        if (timer_queue.head == NULL)
        {
            timer_queue.head = node;
            timer_queue.tail = node;
        }
        else if (time < timer_queue.head->time) 
        {
            node->next = timer_queue.head;
            timer_queue.head = node;
        } else {
            timer_queue_node_t *prev = timer_queue.head;
            timer_queue_node_t *curr = timer_queue.head->next;
            while (curr != NULL && time > curr->time) 
            {
                prev = curr;
                curr = curr->next;
            }
            prev->next = node;
            node->next = curr;
            if (curr == NULL) 
            {
                timer_queue.tail = node;
            }
        }
        return node;
    }
   else
   {
    return NULL;
   }
}

static void timer_queue_remove_node(timer_queue_node_t *node) 
{    
    if (timer_queue.head == node) 
    {
        timer_queue.head = node->next;
        if (timer_queue.head == NULL) 
        {
            timer_queue.tail = NULL;
        }
    } 
    else 
    {
        timer_queue_node_t *prev = timer_queue.head;
        while (prev != NULL && prev->next != node) {
            prev = prev->next;
        }
        if (prev != NULL) {
            prev->next = node->next;
        }
    }
    if (timer_queue.tail == node) 
    {
        timer_queue.tail = NULL;
    }

    mem_free(node);
}

static retval timer_queue_pop() {
    timer_queue_node_t *node = timer_queue.head;
    if(node)
    {
        // if(node->scheduling_event.period_num > 0)
        // {
        //     node->scheduling_event.scheduled_time += node->scheduling_event.period_time;
        //     node->scheduling_event.period_num -= 1;
        //     timer_queue_push(queue, node->scheduling_event);
        // }
        // else if(node->scheduling_event.period_num == (uint16_t)-1)
        // {
        //     node->scheduling_event.scheduled_time += node->scheduling_event.period_time;
        //     timer_queue_push(queue, node->scheduling_event);
        // }

        timer_queue_remove_node(node);
        return RET_OK;
    }
    else
    {
        return RET_ERR;
    }
}

timer_handler timer_set(ltime_t time, timer_callback callback, timer_parameter parameter)
{
    if(time == 0) time = 1;
    return timer_queue_push(local_time + time, callback, parameter);
}

void timer_unset(timer_handler timer)
{
    if(timer)
    {
        timer_queue_remove_node(timer);
    }
}

void timer_ticker(void)
{
    ++local_time;

    while(timer_queue.head != NULL)
    {
        if(timer_queue.head->time <= local_time)
        {
            if(timer_queue.head->callback)
            {
                timer_queue.head->callback(timer_queue.head->parameter);
            }
            timer_queue_pop();
        }
        else
        {
            break;
        }
    }    
}
