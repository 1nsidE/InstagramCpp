//
// Created by inside on 6/17/16.
//

#ifndef INSTAGRAM_CPP_HTTPFAILEDTOSEND_H
#define INSTAGRAM_CPP_HTTPFAILEDTOSEND_H

#include "HttpBaseException.h"

struct HttpFailedToSend : public HttpBaseException{
    HttpFailedToSend(const std::string& err_msg) : HttpBaseException{err_msg} {}
    HttpFailedToSend(const char* err_msg) : HttpBaseException{err_msg} {}
    HttpFailedToSend(const HttpFailedToSend& http_failed_to_send) : HttpBaseException{http_failed_to_send} {}

    virtual ~HttpFailedToSend() {}
};

#endif //INSTAGRAM_CPP_HTTPFAILEDTOSEND_H
