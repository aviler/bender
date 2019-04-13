cmake_minimum_required(VERSION 3.13)
project(bender C)

set(CMAKE_C_STANDARD 99)

add_executable(bender main.c parse.h parse.c)