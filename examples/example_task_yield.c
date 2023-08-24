#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "unistd.h"

#include "task.h"

task_t task1, task2;
int who_is_taking_control = 2;

task_entry(task1_entry)
{
    task_begin();

    printf("Task 1 start\n");

    while(1)
    {
        task_wait_until(who_is_taking_control != 2);

        printf("Task 1 take control\n");

        sleep(1);

        who_is_taking_control = 2;

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
        task_wait_until(who_is_taking_control != 1);

        printf("Task 2 take control\n");

        sleep(1);

        who_is_taking_control = 1;

        task_yield();
    }
    task_exit();
}

int main()
{
    task_init(&task1, "Task1", 0, task1_entry, NULL);
    task_init(&task2, "Task2", 0, task2_entry, NULL);

    while(1)
    {
        task1.entry(&task1);
        task2.entry(&task2);
    }

    return 0;
}