cmake_minimum_required(VERSION 2.8.11)

set(HTTP_SOURCES
FormData.cpp
Http.cpp
HttpClient.cpp
HttpHeader.cpp
HttpRequest.cpp
HttpResponse.cpp
HttpUrl.cpp
)

add_library(httpcpp SHARED ${HTTP_SOURCES}
    $<TARGET_OBJECTS:sockets>
)


if(DEFINED OPENSSL_INCLUDE)
    include_directories(${OPENSSL_INCLUDE})
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    add_definitions(-DHTTP_LIB_EXPORT)

    set(CRYPTO_LIB_NAME "libeay32")
    set(SSL_LIB_NAME "ssleay32")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    set(CRYPTO_LIB_NAME "cyrpto")
    set(SSL_LIB_NAME "ssl")
endif()

message("Searching for openssl in: " ${OPENSSL_LIB})

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

if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	target_link_libraries(httpcpp ${SSL_LIB} ${CRYPTO_LIB} "Ws2_32.lib")
elseif(CMAKE_COMPILER_IS_GNUCXX)
	target_link_libraries(httpcpp ${SSL_LIB} ${CRYPTO_LIB})
endif()

message("SSL library path is:  " ${SSL_LIB})
message("Crypto library path is: " ${CRYPTO_LIB})
