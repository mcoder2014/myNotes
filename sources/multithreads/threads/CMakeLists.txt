set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/threads/bin)

link_libraries(/usr/lib)

# create multithreads
add_executable(thread_create thread_create.cpp)
target_link_libraries(thread_create -lpthread)

#get other thread exit code
add_executable(thread_exit thread_exit_status.cpp)
target_link_libraries(thread_exit -lapue -lpthread )