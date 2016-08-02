cmake_minimum_required(VERSION 2.8.11)

add_subdirectory(results)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_definitions(-DINSTAGRAM_LIB_EXPORT)

    if(DEFINED JSON_LIB_DIR)
    	find_library(JSON_LIB_NAME NAMES "jsoncpp" "libjson" "libjsoncpp" PATHS ${JSON_LIB_DIR})
    endif()

    if(DEFINED JSON_INCLUDE_DIR)
    	include_directories(${JSON_INCLUDE_DIR})
    endif()

   
elseif(CMAKE_COMPILER_IS_GNUCXX)
	find_library(JSON_LIB_NAME NAMES "jsoncpp" "libjson" "libjsoncpp" PATHS ${JSON_LIB_DIR})
endif()

set(INSTAGRAM_SOURCES 
    InstagramClient.cpp
    InstagramParser.cpp
)

add_library(instagramcpp SHARED ${INSTAGRAM_SOURCES}
    $<TARGET_OBJECTS:results>
)

if(NOT DEFINED JSON_LIB_NAME)
	set(JSON_LIB_NAME "jsoncpp")
endif()

target_link_libraries(instagramcpp httpcpp ${JSON_LIB_NAME})
