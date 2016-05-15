cmake_minimum_required(VERSION 2.8)

set(HTTP_SOURCES
FormData.cpp
Http.cpp
HttpClient.cpp
HttpHeaderParser.cpp
HttpRequest.cpp
HttpResponse.cpp
)

add_library(http OBJECT ${HTTP_SOURCES})
