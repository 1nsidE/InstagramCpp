project(instagram_cpp)
cmake_minimum_required(VERSION 2.8.8)

if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wpedantic -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -s")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -std=c++1z")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message(STATUS "MSVC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /GX /LDd /MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GX /LD /MD")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DEXP_STL")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(sockets)
add_subdirectory(http)
add_subdirectory(instagram)

file(GLOB HTTP_HEADERS ${PROJECT_SOURCE_DIR}/http/inc/*.h ${PROJECT_SOURCE_DIR}/http/src/exceptions/*.h ${PROJECT_SOURCE_DIR}/sockets/inc/*.h )
file(GLOB INSTAGRAM_HEADERS ${PROJECT_SOURCE_DIR}/instagram/inc/*.h ${PROJECT_SOURCE_DIR}/instagram/src/results/inc/*.h)

file(COPY ${HTTP_HEADERS} DESTINATION ${PROJECT_SOURCE_DIR}/lib/http)
file(COPY ${INSTAGRAM_HEADERS} DESTINATION ${PROJECT_SOURCE_DIR}/lib/instagram)
