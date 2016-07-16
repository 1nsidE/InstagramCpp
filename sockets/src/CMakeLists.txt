cmake_minimum_required(VERSION 2.8.8)

set(SOCKETS_SOURCES 
	SSLSocket.cpp 
	TCPSocket.cpp
	ConnectionListener.cpp
)

add_library(sockets OBJECT ${SOCKETS_SOURCES})
