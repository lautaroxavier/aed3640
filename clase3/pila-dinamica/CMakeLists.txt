cmake_minimum_required(VERSION 3.26)
project(pila_dinamica C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(pila_dinamica
        pila-dinamica.c
        pila-dinamica.h
        main.c)
