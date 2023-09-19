cmake_minimum_required(VERSION 3.26)
project(pila_estatica C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(pila_estatica
        queue.c
        queue.h
        main.c)
