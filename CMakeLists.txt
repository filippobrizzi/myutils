cmake_minimum_required(VERSION 2.8)
Project (my_util)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules  ${CMAKE_MODULE_PATH})

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

include_directories(include)

add_executable(test_count_iterator test/count_iterator_test.cpp)
add_executable(test_csv test/csv_test.cpp)
add_executable(test_is_any test/is_any_test.cpp)
add_executable(test_map_iterator test/map_iterator_test.cpp)
add_executable(test_raii test/serialization_test.cpp)
add_executable(test_string_parser test/string_parser_test.cpp)