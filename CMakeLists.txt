cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(cppzip LANGUAGES CXX)

add_subdirectory(third_party/tcb)

add_library(cppzip INTERFACE)
target_sources(cppzip INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/cppzip/cppzip.hpp)
target_include_directories(cppzip INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(cppzip INTERFACE span)

add_executable(cppzip_test test/test.cpp)
target_link_libraries(cppzip_test cppzip)

