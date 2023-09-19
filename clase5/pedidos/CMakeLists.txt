cmake_minimum_required(VERSION 3.26)
project(pedidos C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(pedidos
        pedidos.c
        pedidos.h)
