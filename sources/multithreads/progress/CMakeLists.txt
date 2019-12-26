set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/progress/bin)

# test atexit and env
add_executable(my_atexit my_atexit.cpp)

# test resource limit
add_executable(test_limit test_limt.cpp)

# test fork
add_executable(test_fork test_fork.cpp)

# test vfork
add_executable(test_vfork test_vfork.cpp)

# test wait
add_executable(test_wait test_wait.cpp)

# fork twice
add_executable(test_fork_twice fork_twice.cpp)

# with compete
add_executable(with_compete with_compete.cpp)

# with ipc
add_executable(with_ipc with_ipc.cpp)