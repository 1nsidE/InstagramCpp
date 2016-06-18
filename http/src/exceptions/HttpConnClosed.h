//
// Created by inside on 6/17/16.
//

#ifndef INSTAGRAM_CPP_HTTPCONNCLOSED_H
#define INSTAGRAM_CPP_HTTPCONNCLOSED_H

#include "HttpBaseException.h"

struct HttpConnClosed : public HttpBaseException{
    HttpConnClosed(const std::string& err_msg) : HttpBaseException{err_msg} {}
    HttpConnClosed(const char* err_msg) : HttpBaseException{err_msg} {}
    HttpConnClosed(const HttpConnClosed& http_conn_closed) : HttpBaseException{http_conn_closed} {}

    virtual ~HttpConnClosed(){}
};

#endif //INSTAGRAM_CPP_HTTPCONNCLOSED_H
