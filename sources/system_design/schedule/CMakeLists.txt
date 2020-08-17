cmake_minimum_required(VERSION 3.1)
project(SCHEDULE)

# output path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

message("output path ${EXECUTABLE_OUTPUT_PATH}")
message("output library path ${LIBRARY_OUTPUT_PATH}")

set(SCHEDULE_HEADERS 
    include/schedule.h)

set(SCHEDULE_SOURCES
    src/schedule.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)
# library
add_library(schedule SHARED ${SCHEDULE_HEADERS} ${SCHEDULE_SOURCES})

# example
add_subdirectory(example)
