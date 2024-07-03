cmake_minimum_required(VERSION 3.25)
project(Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)

file(GLOB GEOMETRY_HEADERS *.h *.hpp)
file(GLOB GEOMETRY_SRC *.c *.cpp)

add_library(geometry STATIC
            #${GEOMETRY_HEADERS} 
            ${GEOMETRY_SRC})
target_include_directories(geometry PUBLIC ${GEOMETRY_HEADERS})


