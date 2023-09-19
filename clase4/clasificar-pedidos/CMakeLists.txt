cmake_minimum_required(VERSION 3.26)
project(clasificar_pedidos C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(clasificar_pedidos
        clasificar.c
        clasificar.h)
