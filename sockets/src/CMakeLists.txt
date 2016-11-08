cmake_minimum_required(VERSION 2.8.8)

if(DEFINED GNUTLS_INCLUDE)
    include_directories(${GNUTLS_INCLUDE})
endif()

set(SOCKETS_SOURCES
        SSLSocket.cpp 
        ConnectionListener.cpp)

if(UNIX AND NOT APPLE)
    set(TCP_SOCKET TCPSocketLinux.cpp)
elseif(WIN32)
    set(TCP_SOCKET TCPSocketWin.cpp)
endif()

add_library(sockets OBJECT ${SOCKETS_SOURCES} ${TCP_SOCKET})
