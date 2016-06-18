//
// Created by inside on 6/17/16.
//

#ifndef INSTAGRAM_CPP_HTTPCONNREFUSED_H
#define INSTAGRAM_CPP_HTTPCONNREFUSED_H

#include "HttpBaseException.h"

struct HttpConnRefused : public HttpBaseException{
    HttpConnRefused(const std::string& err_msg) : HttpBaseException{err_msg} {}
    HttpConnRefused(const char* err_msg) : HttpBaseException{err_msg} {}
    HttpConnRefused(const HttpConnRefused& http_conn_refused) : HttpBaseException{http_conn_refused}{}

    virtual ~HttpConnRefused(){}
};

#endif //INSTAGRAM_CPP_HTTPCONNREFUSED_H
