cmake_minimum_required(VERSION 3.17)
project(Auxiliary)




file(GLOB_RECURSE SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER ${CMAKE_SOURCE_DIR}/include/*.hpp ${CMAKE_SOURCE_DIR}/include/*.h)
# add_library(auxiliary SHARED)
add_executable(auxiliary)
target_sources(auxiliary PRIVATE ${SRC})
target_include_directories(auxiliary PRIVATE ${CMAKE_SOURCE_DIR}/include)



