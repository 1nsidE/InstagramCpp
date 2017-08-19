cmake_minimum_required(VERSION 2.8.8)

include_directories(${HEADERS_DIR})
include_directories(${HEADERS_DIR}/results)
set(RESULT_SOURCES
    BaseResult.cpp
    AuthorizationToken.cpp
    MediaEntry.cpp
    UserInfo.cpp
    RelationshipInfo.cpp
    TagInfo.cpp
    CommentInfo.cpp
    LocationInfo.cpp
)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    add_definitions(-DINSTAGRAM_LIB_EXPORT)
endif()

add_library(results OBJECT ${RESULT_SOURCES})
