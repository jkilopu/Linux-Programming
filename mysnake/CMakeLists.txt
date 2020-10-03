# 最低CMake版本要求
cmake_minimum_required(VERSION 3.12.0)

# 项目名称
project(mysnake)

#设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# 头文件路径
aux_source_directory(. source)
add_executable(${PROJECT_NAME} ${source})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/inc)
# 添加库啊啊啊啊！！！
target_link_libraries(${PROJECT_NAME} ncurses)
