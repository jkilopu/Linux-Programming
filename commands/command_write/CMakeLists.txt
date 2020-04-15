# 最低CMake版本要求
cmake_minimum_required(VERSION 3.10.0)

# 项目名称
project(write)

#设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

#添加子目录，使子目录中的CMakelists.txt被执行
add_subdirectory(test)