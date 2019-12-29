cmake_minimum_required(VERSION 3.16)
project(ML_THREADS)

# build apue cpp libary
add_subdirectory(apue)

include_directories(${PROJECT_SOURCE_DIR}/apue/include)
link_directories(${PROJECT_BINARY_DIR}/libs)
# include_directories(${PROJECT_SOURCE_DIR}/apue.3e/include)
# link_directories(${PROJECT_SOURCE_DIR}/apue.3e/lib)
link_libraries(apue)

add_subdirectory(progress)
add_subdirectory(threads)
add_subdirectory(signals)