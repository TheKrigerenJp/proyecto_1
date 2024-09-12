cmake_minimum_required(VERSION 3.28)
project(proyecto_1)

set(CMAKE_CXX_STANDARD 17)

add_library(proyecto_1 STATIC
        ListaDoble.cpp
        ListaDoble.h
        MPointerGC.cpp
        MPointerGC.h
        2MPointer.cpp
        2MPointer.h)
