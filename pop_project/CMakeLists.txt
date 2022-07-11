cmake_minimum_required(VERSION 3.21)
project(pop_project C)

set(CMAKE_C_STANDARD 99)

add_executable(pop_project main.c project.h project.c)
