set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/signals/bin)

# 捕捉信号
add_executable(test_sigusr sigusr.cpp)