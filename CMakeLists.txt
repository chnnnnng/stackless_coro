cmake_minimum_required(VERSION 3.10)

# set the project name
project(Stackless_Coro)

# build type = debug
set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")

add_compile_options(-O0 -Wall -g)

add_compile_options(-DLOG_COMPLEX)
add_compile_options(-DLOG_LEVEL_DEBUG)

ADD_SUBDIRECTORY(examples)
ADD_SUBDIRECTORY(coro)
