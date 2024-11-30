cmake_minimum_required(VERSION 3.20)

project(Lab5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

# --- Компиляция основной программы ---
add_executable(lab5 ${SRC_DIR}/lab5.cpp ${CMAKE_SOURCE_DIR}/main.cpp)
target_include_directories(lab5 PRIVATE ${INCLUDE_DIR})

# --- Компиляция тестов ---
enable_testing()

# Создание исполняемого файла для тестов
add_executable(tests_lab5 ${TEST_DIR}/test.cpp ${SRC_DIR}/lab5.cpp)

# Подключение библиотек Google Test к тестовому файлу
target_link_libraries(tests_lab5 PRIVATE gtest_main)
target_include_directories(tests_lab5 PRIVATE ${INCLUDE_DIR} ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}/googletest/include)

# Добавление тестов в CTest
add_test(NAME Lab5Tests COMMAND tests_lab5)
