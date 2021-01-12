cmake_minimum_required(VERSION 2.8)
project(imageBasics)
set(CMAKE_BUILD_TYPE "Debug")
# 添加c++ 11标准支持
set(CMAKE_CXX_FLAGS "-std=c++11 -O2")

# 寻找OpenCV库
find_package(OpenCV REQUIRED)

add_executable(a_imageBasics a_imageBasics.cpp)
target_link_libraries(a_imageBasics ${OpenCV_LIBS})

add_executable(b_imageBasics b_imageBasics.cpp)
target_link_libraries(b_imageBasics ${OpenCV_LIBS})

add_executable(c_imageBasics c_imageBasics.cpp)
target_link_libraries(c_imageBasics ${OpenCV_LIBS})

add_executable(d_imageBasics d_imageBasics.cpp)
target_link_libraries(d_imageBasics ${OpenCV_LIBS})

add_executable(e_imageBasics e_imageBasics.cpp)
target_link_libraries(e_imageBasics ${OpenCV_LIBS})

