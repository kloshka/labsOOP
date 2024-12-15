cmake_minimum_required(VERSION 3.22.1)
project(lw7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(main main.cpp)
add_library(${PROJECT_NAME} ${SOURCES})
add_executable(test tests.cpp)

target_link_libraries(main PRIVATE ${PROJECT_NAME})
target_include_directories(test PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(test PRIVATE gtest gtest_main ${PROJECT_NAME})