cmake_minimum_required(VERSION 3.10)

project(FiguresProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(FiguresProject
    main.cpp           
    src/Array.cpp 
    src/Rhombus.cpp
    src/Pentagon.cpp
    src/Hexagon.cpp
    src/Point.cpp
    src/Figure.cpp    
)

target_include_directories(FiguresProject PUBLIC ${PROJECT_SOURCE_DIR}/include)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF)
set(INSTALL_GTEST OFF)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(Tests
    tests/test.cpp          
    src/Array.cpp 
    src/Rhombus.cpp
    src/Pentagon.cpp
    src/Hexagon.cpp
    src/Point.cpp
    src/Figure.cpp      
)

target_include_directories(Tests PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(Tests gtest_main)

add_test(NAME AllTests COMMAND Tests)