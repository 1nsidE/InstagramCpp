cmake_minimum_required(VERSION 2.8.8)

set(RESULT_SOURCES
BaseResult.cpp
AuthorizationToken.cpp
MediaEntries.cpp
MediaEntry.cpp
UserInfo.cpp
UsersInfo.cpp
RelationshipInfo.cpp
TagInfo.cpp
TagsInfo.cpp
CommentInfo.cpp
CommentsInfo.cpp
LocationInfo.cpp
LocationsInfo.cpp
)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_definitions(-DINSTAGRAM_LIB_EXPORT)
endif()

add_library(results OBJECT ${RESULT_SOURCES})
