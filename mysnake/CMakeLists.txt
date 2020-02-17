# 最低CMake版本要求
cmake_minimum_required(VERSION 3.10.0)

# 项目名称
project(mysnake)

#设置输出路径（与源文件在同一个文件夹下）
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

# 头文件路径
include_directories(./inc)
aux_source_directory(. source)
add_executable(mysnake ${source})
# 添加库啊啊啊啊！！！
target_link_libraries(mysnake curses)