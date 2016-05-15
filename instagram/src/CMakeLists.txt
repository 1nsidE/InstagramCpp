cmake_minimum_required(VERSION 2.8)

add_subdirectory(results)

set(INSTAGRAM_SOURCES 
	InstagramClient.cpp
	InstagramParser.cpp
)

add_library(instagram SHARED ${INSTAGRAM_SOURCES}
    $<TARGET_OBJECTS:http>
    $<TARGET_OBJECTS:sockets>
    $<TARGET_OBJECTS:results>
)
target_link_libraries(instagram jsoncpp ssl crypto)
