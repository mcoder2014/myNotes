set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/threads/bin)

link_directories(/usr/lib ${PROJECT_BINARY_DIR}/libs)
link_libraries(apue pthread)

# create multithreads
# add_executable(thread_create thread_create.cpp)
# target_link_libraries(thread_create -lpthread)

# 编译路径下的多个 cpp 文件
aux_source_directory(. TEST_SCRIPT)
message(${TEST_SCRIPT})

foreach(filename ${TEST_SCRIPT})
    get_filename_component(mainname ${filename} NAME_WE)
    message("Build script file: ${filename}")
    message("add_executable(${mainname} ${filename})")
    add_executable(${mainname} ${filename})
endforeach()

# #get other thread exit code
# add_executable(thread_exit thread_exit_status)
# target_link_libraries(thread_exit -lapue -lpthread )

# add_executable(badexit2 badexit2)
# target_link_libraries(badexit2 -lapue -lpthread )