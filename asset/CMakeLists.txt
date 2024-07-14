cmake_minimum_required(VERSION 3.25)
project(Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)

file(GLOB ASSET_HEADERS *.h *.hpp)
file(GLOB ASSET_SRC *.c *.cpp)

add_library(asset STATIC
            ${ASSET_HEADERS} 
            ${ASSET_SRC})
target_include_directories(asset PUBLIC ${asset})


