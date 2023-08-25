#pragma once 

#include "common.h"

typedef struct timer_queue_node_t * timer_handler;

typedef void * timer_parameter;

typedef void (*timer_callback)(timer_parameter);

timer_handler timer_set(ltime_t time, timer_callback callback, timer_parameter parameter);

void timer_ticker(void);