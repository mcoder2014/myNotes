cmake_minimum_required(VERSION 3.16)
project(LEETCODES)

# 编译路径下的多个 cpp 文件
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

aux_source_directory(./src TEST_SCRIPT)
message(${TEST_SCRIPT})

foreach(filename ${TEST_SCRIPT})
    get_filename_component(mainname ${filename} NAME_WE)
    message("Build script file: ${filename}")
    message("add_executable(${mainname} ${filename})")
    add_executable(${mainname} ${filename})
endforeach()
