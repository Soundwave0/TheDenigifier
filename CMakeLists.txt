cmake_minimum_required(VERSION 3.16)
project(TheDenigifier VERSION 0.1)

enable_language(C)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    ptom.c
)

add_executable(TheDenigifier ${SOURCES})

target_link_libraries(TheDenigifier PRIVATE Qt6::Core Qt6::Widgets z)

set_target_properties(TheDenigifier PROPERTIES AUTOMOC ON)