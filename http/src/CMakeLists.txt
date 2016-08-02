cmake_minimum_required(VERSION 2.8.11)

set(HTTP_SOURCES
FormData.cpp
Http.cpp
HttpClient.cpp
HttpHeaderParser.cpp
HttpHeader.cpp
HttpRequest.cpp
HttpResponse.cpp
HttpUrl.cpp
)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_definitions(-DHTTP_LIB_EXPORT)
endif()

add_library(httpcpp SHARED ${HTTP_SOURCES}
    $<TARGET_OBJECTS:sockets>
)
target_link_libraries(httpcpp gnutls)
