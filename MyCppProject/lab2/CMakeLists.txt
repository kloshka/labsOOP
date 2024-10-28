cmake_minimum_required(VERSION 3.10)
project(test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавление библиотеки с вашим классом для первой лабораторной работы
add_library(lab1_lib src/lab1_16.cpp)
add_executable(lab1_exe main_lab1_16.cpp)
target_link_libraries(lab1_exe PRIVATE lab1_lib)

# Добавление библиотеки с классом Hex для второй лабораторной работы
add_library(lab2_lib src/lab2_2.cpp)

# Создание исполняемого файла для второй лабораторной работы
add_executable(lab2_exe main_lab2_2.cpp)

# Присоединяем библиотеку lab2 к исполняемому файлу lab2_exe
target_link_libraries(lab2_exe PRIVATE lab2_lib)

# Добавление тестов
enable_testing()

# Создание исполняемого файла для тестов первой лабораторной работы
add_executable(gtests_lab1 tests/test_lab1_16.cpp)
target_link_libraries(gtests_lab1 PRIVATE lab1_lib gtest_main)

# Создание исполняемого файла для тестов второй лабораторной работы
add_executable(gtests_lab2 tests/test_lab2_2.cpp)
target_link_libraries(gtests_lab2 PRIVATE lab2_lib gtest_main)

# Добавление тестов в тестовые наборы
add_test(NAME Lab1Tests COMMAND gtests_lab1)
add_test(NAME Lab2Tests COMMAND gtests_lab2)
