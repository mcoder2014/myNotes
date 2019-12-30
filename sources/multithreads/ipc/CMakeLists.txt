set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

link_directories(/usr/lib ${PROJECT_BINARY_DIR}/libs)
link_libraries(pthread)

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
