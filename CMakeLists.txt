cmake_minimum_required(VERSION 3.25)
project(Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_subdirectory("display")
add_subdirectory("geometry")
add_subdirectory("asset")

find_package(SDL2 REQUIRED)
#find_package(Eigen3 REQUIRED)
#include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})

#reveal compiler Commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC 
    ${SDL2_LIBRARIES} 
    #${Eigen3_LIBRARIES} 
    display
    geometry
    asset)

#specify compiler std version
target_compile_features(main PUBLIC cxx_std_23)
