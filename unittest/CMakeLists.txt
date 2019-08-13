cmake_minimum_required(VERSION 3.10)
project(unittest)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "src/*.cpp")
file(GLOB LIBS "${CMAKE_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM LIBS "${CMAKE_SOURCE_DIR}/src/main.cpp")

add_executable(unittest ${SOURCES} ${LIBS})
include_directories(${CMAKE_SOURCE_DIR}/external)
include_directories(${CMAKE_SOURCE_DIR}/src)
