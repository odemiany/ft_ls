cmake_minimum_required(VERSION 3.8)
project(ft_ls)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")
set(SOURCE_FILES main.c parse_params.c check_flags.c sorting.c split_dir_and_not_dir.c list_function.c operate_not_dir.c operate_dir.c)

include_directories(libft/includes)

link_directories(libft)

add_executable(ft_ls ${SOURCE_FILES})

target_link_libraries(ft_ls libft.a)