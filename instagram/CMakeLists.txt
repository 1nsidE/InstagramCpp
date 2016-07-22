cmake_minimum_required(VERSION 2.8.8)

include_directories(
    inc 
    src/results/inc 
    ${PROJECT_SOURCE_DIR}/http/inc
    ${PROJECT_SOURCE_DIR}/sockets/inc
)

add_subdirectory(src)
