cmake_minimum_required(VERSION 3.14)
find_package(Zephyr hint $ENV{ZEPHYR_BASE})

project(copOnZephyr)

target_sources(app PRIVATE src/main.cpp)

target_link_libraries(app
    PRIVATE
        cop::cop
)

