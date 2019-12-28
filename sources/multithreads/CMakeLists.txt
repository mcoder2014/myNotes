project(ML_THREADS)

include_directories(${PROJECT_SOURCE_DIR}/apue.3e/include)
link_directories(${PROJECT_SOURCE_DIR}/apue.3e/lib)
link_libraries(libapue.a)

add_subdirectory(progress)

add_subdirectory(threads)

add_subdirectory(signals)