//
// Created by inside on 6/17/16.
//

#ifndef INSTAGRAM_CPP_HTTPTOOBIGRESPONSE_H
#define INSTAGRAM_CPP_HTTPTOOBIGRESPONSE_H

#include "HttpBaseException.h"

struct HttpTooBigResponse : public HttpBaseException{
    HttpTooBigResponse(const std::string& err_msg) : HttpBaseException{err_msg} {}
    HttpTooBigResponse(const char* err_msg) : HttpBaseException{err_msg} {}
    HttpTooBigResponse(const HttpTooBigResponse& http_big_response) : HttpBaseException{http_big_response} {}

    virtual ~HttpTooBigResponse() {}
};

#endif //INSTAGRAM_CPP_HTTPTOOBIGRESPONSE_H
