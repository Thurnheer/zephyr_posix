cmake_minimum_required(VERSION 3.14)
find_package(Zephyr HINTS $ENV{ZEPHYR_BASE})

project(copOnZephyr)

target_link_libraries(app
    PRIVATE
        cop::cop
)

target_sources(app
    PRIVATE
        src/main.cpp
)

