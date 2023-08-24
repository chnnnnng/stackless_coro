#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "unistd.h"
#include "memory.h"
#include "task.h"

task_t * task1, * task2, *task3;

task_entry(task1_entry)
{
    static int count = 5;

    task_begin();

    printf("Task 1 start\n");

    while(1)
    {
        printf("Task 1 take control, %d\n", count--);

        if(count <= 0){printf("%s end\n", task->name); task_exit();}

        sleep(1);

        task_yield();
    }

    task_exit();
}

task_entry(task2_entry)
{
    static int count = 10;

    task_begin();

    printf("Task 2 start\n");

    while(1)
    {
        printf("Task 2 take control, %d\n", count--);

        if(count <= 0){printf("%s end\n", task->name); task_exit();}

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

    printf("Task 1 and Task 2 Completed\n");

    printf("Now Back to Task 3\n");

    printf("Task 3 over\n");

    task_exit();
}

int main()
{
    task_create(task3, "Task3", 0, task3_entry, NULL);

    task_start_scheduler();

    return 0;
}