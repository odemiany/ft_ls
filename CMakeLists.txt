cmake_minimum_required(VERSION 3.8)
project(ft_ls)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES ft_ls.h main.c)
add_executable(ft_ls ${SOURCE_FILES})