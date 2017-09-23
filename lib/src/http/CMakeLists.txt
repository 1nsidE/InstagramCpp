cmake_minimum_required(VERSION 2.8.11)

add_subdirectory(sockets)

include_directories(${HEADERS_DIR}/http)
set(HTTP_SOURCES
    FormData.cpp
    Http.cpp
    HttpClient.cpp
    HttpHeader.cpp
    HttpRequest.cpp
    HttpResponse.cpp
    HttpUrl.cpp
)

if(DEFINED OPENSSL_INCLUDE)
    include_directories(${OPENSSL_INCLUDE})
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    add_definitions(-DHTTP_LIB_EXPORT)
endif()

add_library(http OBJECT ${HTTP_SOURCES})
