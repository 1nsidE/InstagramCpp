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

find_library(GNUTLS_LIB_NAME NAMES "gnutls" "libgnutls" HINTS ${GNUTLS_LIB})

if(DEFINED GNUTLS_INCLUDE)
    include_directories(${GNUTLS_INCLUDE})
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_definitions(-DHTTP_LIB_EXPORT)

    if(NOT GNUTLS_LIB_NAME)
        set(GNUTLS_LIB_NAME ${GNUTLS_LIB}\\libgnutls.dll.a)
    endif()

    target_link_libraries(httpcpp ${GNUTLS_LIB_NAME} "Ws2_32.lib")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    if(NOT GNUTLS_LIB_NAME)
        set(GNUTLS_LIB_NAME "gnutls")
    endif()
    
    target_link_libraries(httpcpp ${GNUTLS_LIB_NAME})
endif()


message("GnuTLS library path is " ${GNUTLS_LIB_NAME})
