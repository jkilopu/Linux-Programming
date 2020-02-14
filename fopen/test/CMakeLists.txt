#为APP_SOURCES变量赋予所有.c文件的值
file( GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/ *.c )

#为每一个.c文件创建可执行文件
foreach(sourcefile IN LISTS APP_SOURCES)
string(REPLACE ".c" "" program ${sourcefile}) #string(REPLACE <match-string> <replace-string> <out-var> <input>...)
add_executable(${program} ${sourcefile})
endforeach(sourcefile)
