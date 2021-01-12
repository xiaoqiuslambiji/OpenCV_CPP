cmake_minimum_required(VERSION 2.8)
project(imageBasics)
set(CMAKE_BUILD_TYPE "Debug")
# 添加c++ 11标准支持
set(CMAKE_CXX_FLAGS "-std=c++11 -O2")

# 寻找OpenCV库
find_package(OpenCV REQUIRED)

add_executable(a_basis a_basis.cpp)
target_link_libraries(a_basis ${OpenCV_LIBS})

add_executable(b_basis b_basis.cpp)
target_link_libraries(b_basis ${OpenCV_LIBS})

add_executable(c_basis c_basis.cpp)
target_link_libraries(c_basis ${OpenCV_LIBS})

add_executable(d_basis d_basis.cpp)
target_link_libraries(d_basis ${OpenCV_LIBS})

add_executable(e_basis e_basis.cpp)
target_link_libraries(e_basis ${OpenCV_LIBS})


