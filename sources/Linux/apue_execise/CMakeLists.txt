cmake_minimum_required(VERSION 3.16)
project(ML_THREADS)

# build apue cpp libary
add_subdirectory(apue)

# using apue library
include_directories(${PROJECT_SOURCE_DIR}/apue/include)
link_directories(${PROJECT_BINARY_DIR}/libs)

link_libraries(apue)    # add apue to all exe

# the examples about progress
add_subdirectory(progress)

# the examples about threads
add_subdirectory(threads)

#the examples about signals
add_subdirectory(signals)

# add ipc
add_subdirectory(ipc)

# socket
add_subdirectory(socket)