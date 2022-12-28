cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(detection)

find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenCV_CXX_FLAGS}")

add_executable(tests test/test.cpp)
add_executable(detection main.cpp)

add_library(
    src 
    src/model.cpp
    src/detector.cpp
    src/utils.cpp
)

target_include_directories(detection PUBLIC src/)
target_include_directories(tests PUBLIC src/)

target_link_libraries(src "${OpenCV_LIBS}")
target_link_libraries(detection "${OpenCV_LIBS}")
target_link_libraries(detection src)
target_link_libraries(tests src)

set_property(TARGET detection PROPERTY CXX_STANDARD 14)