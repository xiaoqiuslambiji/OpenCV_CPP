cmake_minimum_required(VERSION 2.8)
project(rename)
set(CMAKE_BUILD_TYPE "Debug")
find_package(OpenCV REQUIRED)# 寻找OpenCV库
add_executable(rename rename.cpp)
target_link_libraries(rename ${OpenCV_LIBS})

