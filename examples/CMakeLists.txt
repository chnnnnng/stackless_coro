INCLUDE_DIRECTORIES(. ../coro)
link_libraries(coro)

# set list
# set( sorcefilelist )
# list( APPEND sorcefilelist sim_common.c argparser.c)

#################################
# 如何运行示例程序？
# add_executable(main 想要运行的示例源文件.c)
#################################
add_executable(main example_task_yield.c)