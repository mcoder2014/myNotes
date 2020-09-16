cmake_minimum_required(VERSION 3.1)
project(STL_LEARNING)
set(CMAKE_CXX_STANDARD 17)  

# 编译路径下的多个 cpp 文件
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(./src SRC_FILENAME)
message(${SRC_FILENAME})

foreach(SINGLE_FILENAME ${SRC_FILENAME})
    get_filename_component(BASENAME ${SINGLE_FILENAME} NAME_WE)
    message("Build script file: ${SINGLE_FILENAME}")
    message("add_executable(${BASENAME} ${SINGLE_FILENAME})")
    add_executable(${BASENAME} ${SINGLE_FILENAME})
    # set_property(TARGET ${BASENAME} PROPERTY CXX_STANDARD 11)
endforeach()
