cmake_minimum_required(VERSION 3.26)
project(sumar C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(sumar
        pila.c
        pila.h
        sumar.c)
