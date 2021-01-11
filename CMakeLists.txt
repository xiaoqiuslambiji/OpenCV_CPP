cmake_minimum_required(VERSION 2.8)
project(imageBasics)
set(CMAKE_BUILD_TYPE "Debug")
# 添加c++ 11标准支持
set(CMAKE_CXX_FLAGS "-std=c++11 -O2")

# 寻找OpenCV库
find_package(OpenCV REQUIRED)

add_executable(a-imageBasics a-imageBasics.cpp)
target_link_libraries(a-imageBasics ${OpenCV_LIBS})

add_executable(b-imageBasics b-imageBasics.cpp)
target_link_libraries(b-imageBasics ${OpenCV_LIBS})

add_executable(c-imageBasics c-imageBasics.cpp)
target_link_libraries(c-imageBasics ${OpenCV_LIBS})

add_executable(d-imageBasics d-imageBasics.cpp)
target_link_libraries(d-imageBasics ${OpenCV_LIBS})

add_executable(e-imageBasics e-imageBasics.cpp)
target_link_libraries(e-imageBasics ${OpenCV_LIBS})

