cmake_minimum_required(VERSION 3.25)
project(Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)

file(GLOB_RECURSE DISPLAY_HEADERS *.h *.hpp)
file(GLOB_RECURSE DISPLAY_SRC *.c *.cpp)

add_library(display STATIC
            #${DISPLAY_HEADERS} 
            ${DISPLAY_SRC})
target_include_directories(display PUBLIC ${DISPLAY_HEADERS})


