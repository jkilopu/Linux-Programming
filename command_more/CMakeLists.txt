# 最低CMake版本要求
cmake_minimum_required(VERSION 3.10.0)

# 项目名称
project(more)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

#添加子目录，使子目录中的CMakelists.txt被执行
add_subdirectory(test)