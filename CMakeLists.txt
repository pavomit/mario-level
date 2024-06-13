cmake_minimum_required(VERSION 3.25)

project(mario-level
        VERSION 1.0.0
        LANGUAGES CXX       
        DESCRIPTION "a very simple mario level game in sfml to grasp the platformer concept")

set(CMAKE_CXX_STANDARD         14)
set(CMAKE_C_STANDARD_REQUIRED  ON)
set(CMAKE_CXX_FEATURES         OFF)

set(TARGET_NAME mario-level)


add_executable(${TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
