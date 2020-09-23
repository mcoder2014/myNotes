cmake_minimum_required(VERSION 3.1)
project(GCC_CROSS)

# output path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

message("output path ${EXECUTABLE_OUTPUT_PATH}")
message("output library path ${LIBRARY_OUTPUT_PATH}")

# Compile Config

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER arm-none-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-none-linux-gnueabihf-g++)

set(GCC_CROSS_HEADERS )

set(GCC_CROSS_SOURCES
    src/main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)

# executable
add_executable(byteOrder ${GCC_CROSS_HEADERS} ${GCC_CROSS_SOURCES})