INCLUDE_DIRECTORIES(. ../coro)

link_libraries(coro)

# set list
# set( sorcefilelist )
# list( APPEND sorcefilelist sim_common.c argparser.c)


# add the executable

# add_executable(main example_task_create_and_join.c)
add_executable(main example_sem.c)