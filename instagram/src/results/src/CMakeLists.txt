cmake_minimum_required(VERSION 2.8)

set(RESULT_SOURCES
BaseResult.cpp
MediaEntries.cpp
MediaEntry.cpp
UserInfo.cpp
UsersInfo.cpp
AuthorizationToken.cpp
)

add_library(results OBJECT ${RESULT_SOURCES})
