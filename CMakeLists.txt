cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(detection)

find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenCV_CXX_FLAGS}")

add_executable(detection main.cpp)
target_include_directories(detection PRIVATE src/)
target_link_libraries(detection "${OpenCV_LIBS}")
set_property(TARGET detection PROPERTY CXX_STANDARD 14)