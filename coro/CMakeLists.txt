INCLUDE_DIRECTORIES(.)

aux_source_directory(. src_coro)

add_library(coro ${src_coro})