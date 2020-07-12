cmake_minimum_required(VERSION 3.13)
project(hw10)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(images)

add_executable(hw10
        images/airplane.c
        images/airplane.h
        images/bird.c
        images/bird.h
        images/clouds.c
        images/clouds.h
        images/flightmap.c
        images/flightmap.h
        images/gameover.c
        images/gameover.h
        images/garbage.c
        images/garbage.h
        images/square.c
        images/square.h
        images/start.c
        images/start.h
        images/winscreen.c
        images/winscreen.h
        draw.c
        draw.h
        font.c
        gba.c
        gba.h
        logic.c
        logic.h
        main.c
        Makefile)
