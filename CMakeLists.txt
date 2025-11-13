cmake_minimum_required(VERSION 3.16)
project(TheDenigifier VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Set source files
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    ptom.c
    ptom.h
)

# Create executable
qt_add_executable(TheDenigifier ${PROJECT_SOURCES})

# Link Qt libraries
target_link_libraries(TheDenigifier PRIVATE Qt6::Core Qt6::Widgets)

# Set properties for automoc
set_target_properties(TheDenigifier PROPERTIES
    AUTOMOC ON
)
