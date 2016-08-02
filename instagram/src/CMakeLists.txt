cmake_minimum_required(VERSION 2.8.11)

add_subdirectory(results)

set(INSTAGRAM_SOURCES 
    InstagramClient.cpp
    InstagramParser.cpp
)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_definitions(-DINSTAGRAM_LIB_EXPORT)
endif()


add_library(instagramcpp SHARED ${INSTAGRAM_SOURCES}
    $<TARGET_OBJECTS:results>
)
target_link_libraries(instagramcpp httpcpp jsoncpp)
