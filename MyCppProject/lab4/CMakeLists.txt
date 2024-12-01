cmake_minimum_required(VERSION 3.20)

project(Lab4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Установка Google Test с FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
# Prevents Google Test from overriding project compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Установка путей к директориям
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

# --- Компиляция основной программы ---
add_executable(main
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${SRC_DIR}/Array.tpp
    ${SRC_DIR}/Figure.tpp
    ${SRC_DIR}/Hexagon.tpp
    ${SRC_DIR}/Pentagon.tpp
    ${SRC_DIR}/Rhombus.tpp
    ${SRC_DIR}/Point.tpp
)
target_include_directories(main PRIVATE ${INCLUDE_DIR})

# --- Компиляция тестов ---
enable_testing()

# Создание исполняемого файла для тестов
add_executable(runTests
    ${TEST_DIR}/test.cpp
    ${SRC_DIR}/Array.tpp
    ${SRC_DIR}/Figure.tpp
    ${SRC_DIR}/Hexagon.tpp
    ${SRC_DIR}/Pentagon.tpp
    ${SRC_DIR}/Rhombus.tpp
    ${SRC_DIR}/Point.tpp
)

# Подключение библиотек Google Test к тестовому файлу
target_link_libraries(runTests PRIVATE gtest_main)
target_include_directories(runTests PRIVATE ${INCLUDE_DIR})

# Добавление тестов в CTest
add_test(NAME Lab4Tests COMMAND runTests)
