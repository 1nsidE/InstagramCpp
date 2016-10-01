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

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

    if(DEFINED GNUTLS_LIB)
        find_library(GNUTLS_LIB_NAME NAMES "gnutls" "libgnutls" PATHS ${GNUTLS_LIB})
    endif()

    if(DEFINED GNUTLS_INCLUDE)
        include_directories(${GNUTLS_INCLUDE})
    endif()

    add_definitions(-DHTTP_LIB_EXPORT)

    if(NOT GNUTLS_LIB_NAME AND GNUTLS_LIB)
        set(GNUTLS_LIB_NAME ${GNUTLS_LIB}\\libgnutls.dll.a)
    else()
        set(GNUTLS_LIB_NAME "gnutls")
    endif()
    target_link_libraries(httpcpp ${GNUTLS_LIB_NAME} "Ws2_32.lib")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    find_library(GNUTLS_LIB_NAME NAMES "gnutls" "libgnutls")
    
    if(NOT DEFINED GNUTLS_LIB_NAME)
        set(LIB_GNUTLS_LIB_NAME "gnutls")
    endif()
    target_link_libraries(httpcpp ${GNUTLS_LIB_NAME})
endif()


message("GnuTLS library path is " ${GNUTLS_LIB_NAME})
