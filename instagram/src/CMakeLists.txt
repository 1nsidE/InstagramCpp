cmake_minimum_required(VERSION 2.8.11)

add_subdirectory(results)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    add_definitions(-DINSTAGRAM_LIB_EXPORT)
endif()

if(DEFINED RAPIDJSON_INCLUDE)
    include_directories(${RAPIDJSON_INCLUDE})
endif()

set(INSTAGRAM_SOURCES 
    InstagramClient.cpp
    InstagramParsers.cpp
)

add_library(instagramcpp SHARED ${INSTAGRAM_SOURCES}
    $<TARGET_OBJECTS:results>
)

target_link_libraries(instagramcpp httpcpp)
