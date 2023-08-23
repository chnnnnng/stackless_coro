#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "unistd.h"
#include "memory.h"
#include "task.h"

task_t * task1, * task2, *task3;
int who_is_taking_control = 2;
int count = 5;

task_entry(task1_entry)
{
    task_begin();

    printf("Task 1 start\n");

    while(1)
    {
        task_wait_until(who_is_taking_control != 2);

        if(count) printf("Task 1 take control, %d\n", count--);

        who_is_taking_control = 2;

        if(count <= 0){printf("%s end\n", task->name); task_exit();}

        sleep(1);

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

        if(count)  printf("Task 2 take control, %d\n", count--);

        who_is_taking_control = 1;

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

    task_create(task1, "Task1", 0, task1_entry, NULL);
    task_create(task2, "Task2", 0, task2_entry, NULL);

    task_join(task1, task2); //Same with: task_wait_while(task_schedule(task1) | task_schedule(task2));

    printf("Task 1 and Task 2 Completed\n");

    printf("Now Back to Task 3\n");

    task_delete(task1, task2);

    printf("Task 3 deleted Task 1 and 2\n");

    printf("Task 3 over");

    task_exit();
}

int main()
{
    task_create(task3, "Task3", 0, task3_entry, NULL);
    
    while(task_schedule(task3))
    {
        //如果除了本线程中的3个协程，还有其他的线程需要执行，应该在此处出让CPU运行时间
        //sleep(1);
    }

    task_delete(task3);

    return 0;
}