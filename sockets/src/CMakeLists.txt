cmake_minimum_required(VERSION 2.8.8)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    if(DEFINED GNUTLS_INCLUDE)
        include_directories(${GNUTLS_INCLUDE})
    endif()
    
endif()

set(SOCKETS_SOURCES
    SSLSocket.cpp 
    TCPSocket.cpp
    ConnectionListener.cpp
)

add_library(sockets OBJECT ${SOCKETS_SOURCES})
