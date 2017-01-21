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

find_library(SSL_LIB NAMES "ssl" HINTS ${OPENSSL_LIB})
find_library(CRYPTO_LIB NAMES "crypto" HINTS ${OPENSSL_LIB})

if(DEFINED OPENSSL_INCLUDE)
    include_directories(${OPENSSL_INCLUDE})
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    add_definitions(-DHTTP_LIB_EXPORT)

    if(NOT GNUTLS_LIB_NAME)
        set(GNUTLS_LIB_NAME ${GNUTLS_LIB}\\libgnutls.dll.a)
    endif()

    target_link_libraries(httpcpp ${SSL_LIB} ${CRYPTO_LIB} "Ws2_32.lib")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    if(NOT SSL_LIB)
        set(SSL_LIB "ssl")
    endif()

    if(NOT CRYPTO_LIB)
        set(CRYPTO_LIB "crypto")
    endif()
    
    target_link_libraries(httpcpp ${SSL_LIB} ${CRYPTO_LIB})
endif()


message("SSL library path is:  " ${SSL_LIB})
message("Crypto library path is: " ${CRYPTO_LIB})
