#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "unistd.h"
#include "memory.h"
#include "task.h"
#include "sem.h"

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

        task_yield();
    }

    task_exit();
}

task_entry(task2_entry)
{
    task_begin();

    printf("Task 2 start\n");

    while(1)
    {
        sem_take(&sem);

        printf("Task 2 Toke a Sem\n");

        sleep(1);

        task_yield();
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

int main()
{
    task_create(task3, "Task3", 0, task3_entry, NULL);

    task_start_scheduler();

    return 0;
}