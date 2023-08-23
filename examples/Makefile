CFLAGS=-O -Wuninitialized -Werror -I ..


TARGETSLIST=example_continuation example_task_yield example_task_yield_malloc example_task_hierarchy

all: $(TARGETSLIST)

example_continuation: example_continuation.c

example_task_yield: example_task_yield.c

example_task_yield_malloc: example_task_yield_malloc.c

example_task_hierarchy: example_task_hierarchy.c

.PHONY:clean
clean:
	rm $(TARGETSLIST)