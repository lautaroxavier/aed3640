cmake_minimum_required(VERSION 3.26)
project(cola_dinamica C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(cola_dinamica
        cola.c
        cola.h
        main.c)
