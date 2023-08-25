#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "unistd.h"
#include "memory.h"
#include "task.h"
#include "sem.h"
#include "timer.h"
#include <signal.h>
#include <sys/time.h>

static void tick_callback(void);

task_t * task1, * task2, *task3;
sem_t sem = SEM_INITIAL;

task_entry(task1_entry)
{
    task_begin();

    printf("Task 1 start\n");

    while(1)
    {
        printf("Task 1 Give a Sem\n");

        sem_give(&sem);

        task_sleep(1);      //sleep 1 => wake and act at next tick

        printf("Task 1 Give a Sem\n");

        sem_give(&sem);

        task_sleep(2);
    }

    task_exit();
}

task_entry(task2_entry)
{
    task_begin();

    static int cnt = 0;

    printf("Task 2 start\n");

    while(1)
    {
        sem_take_timeout(&sem, 5);
        if(ret == RET_TO)
        {
            printf("Task 2 Timeout\n");
        }
        else
        {
            printf("Task 2 Toke a Sem, %d\n", cnt++);
        }
    }
    task_exit();
}


task_entry(task3_entry)
{
    task_begin();

    printf("Task 3 start\n");

    printf("Task 3 Create and Start Task 1 and 2\n");

    task_create(task1, "Task1", 1, task1_entry, NULL);
    task_create(task2, "Task2", 1, task2_entry, NULL);

    task_join(task1, task2); //Wait until both task1 and task2 exited

    printf("Task 1 and 2 Completed, Now Back to Task 3\n");

    printf("Task 3 over\n");

    task_exit();
}

void signalHandler(int signo)
{
    switch (signo){
        case SIGALRM:
            tick_callback();
            break;
   }
}

static void tick_callback(void)
{
    timer_ticker();
    printf("--------------\n");
}

int main()
{
    mem_init();

    signal(SIGALRM, signalHandler);
    struct itimerval new_value, old_value;
    new_value.it_value.tv_sec = 1;
    new_value.it_value.tv_usec = 0;
    new_value.it_interval.tv_sec = 1;
    new_value.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &new_value, &old_value);

    task_create(task3, "Task3", 0, task3_entry, NULL);

    task_start_scheduler();

    return 0;
}
