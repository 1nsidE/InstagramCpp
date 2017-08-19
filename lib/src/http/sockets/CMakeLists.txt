cmake_minimum_required(VERSION 2.8.8)

if(DEFINED OPENSSL_INCLUDE)
    include_directories(${OPENSSL_INCLUDE})
endif()

include_directories(${HEADERS_DIR}/http/sockets)
set(SOCKETS_SOURCES
    TCPSocket.cpp
    SSLSocket.cpp
    ConnectionListener.cpp
)

if(UNIX AND NOT APPLE)
    set(TCP_SOCKET TCPSocketLinux.cpp)
elseif(WIN32)
    set(TCP_SOCKET TCPSocketWin.cpp)
endif()

add_library(sockets OBJECT ${SOCKETS_SOURCES} ${TCP_SOCKET})
