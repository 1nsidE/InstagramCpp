cmake_minimum_required(VERSION 2.8.8)

add_subdirectory(http)
add_subdirectory(results)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    add_definitions(-DINSTAGRAM_LIB_EXPORT)
endif()

if(DEFINED RAPIDJSON_INCLUDE)
    message(STATUS "Include rapidjson headers from: " ${RAPIDJSON_INCLUDE})
    include_directories(${RAPIDJSON_INCLUDE})
endif()

include_directories(${HEADERS_DIR})
set(INSTAGRAM_SOURCES
    InstagramClient.cpp
    InstagramParsers.cpp
)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(CRYPTO_LIB_NAME "libeay32")
    set(SSL_LIB_NAME "ssleay32")
elseif(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CRYPTO_LIB_NAME "crypto")
    set(SSL_LIB_NAME "ssl")
endif()

message(STATUS "Searching for openssl in: " ${OPENSSL_LIB})

find_library(SSL_LIB NAMES ${SSL_LIB_NAME} HINTS ${OPENSSL_LIB})
find_library(CRYPTO_LIB NAMES ${CRYPTO_LIB_NAME} HINTS ${OPENSSL_LIB})

if(NOT DEFINED SSL_LIB)
	message("Failed to find SSL lib, setting to default: " ${OPENSSL_LIB}\\${SSL_LIB_NAME})
	set(SSL_LIB ${OPENSSL_LIB}\\${SSL_LIB_NAME})
endif()

if(NOT DEFINED CRYPTO_LIB)
	message("Failed to find Cyrpto lib, setting to default: " ${OPENSSL_LIB}\\${CRYPTO_LIB_NAME})
	set(CRYPTO_LIB ${OPENSSL_LIB}\\${CRYPTO_LIB_NAME})
endif()

add_library(instagramcpp SHARED ${INSTAGRAM_SOURCES}
    $<TARGET_OBJECTS:results>
    $<TARGET_OBJECTS:http>
    $<TARGET_OBJECTS:sockets>
)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	target_link_libraries(instagramcpp ${SSL_LIB} ${CRYPTO_LIB} "Ws2_32.lib")
elseif(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	target_link_libraries(instagramcpp ${SSL_LIB} ${CRYPTO_LIB})
endif()

message(STATUS "SSL library path is:  " ${SSL_LIB})
message(STATUS "Crypto library path is: " ${CRYPTO_LIB})
