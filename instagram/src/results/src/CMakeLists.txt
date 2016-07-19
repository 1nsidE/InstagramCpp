cmake_minimum_required(VERSION 2.8.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

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

add_library(results OBJECT ${RESULT_SOURCES})
