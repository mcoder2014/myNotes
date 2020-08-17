# 配置 library 路径
include_directories(../include)

# 配置输出 exe
add_executable(scheduleExample scheduleExample.cpp)

# 设置属性
set_property(TARGET scheduleExample PROPERTY CXX_STANDARD 11)
link_directories(${LIBRARY_OUTPUT_DIRECTORY}/bin)
target_link_libraries(scheduleExample schedule)