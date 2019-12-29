# build the lib of apue

set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/libs)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include_directories(include)
aux_source_directory(./libs APUELIBS)

add_library(apue ${APUELIBS})
