cmake_minimum_required(VERSION 3.26)
project(toys)

add_executable(main)
target_sources(main
PRIVATE
    toys/main.cpp
)
