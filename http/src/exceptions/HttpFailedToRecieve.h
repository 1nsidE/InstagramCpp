//
// Created by inside on 6/17/16.
//

#ifndef INSTAGRAM_CPP_HTTPFAILEDTORECIEVE_H
#define INSTAGRAM_CPP_HTTPFAILEDTORECIEVE_H

#include "HttpBaseException.h"

struct HttpFailedToRecieve : public HttpBaseException{
    HttpFailedToRecieve(const std::string& err_msg) : HttpBaseException{err_msg} {}
    HttpFailedToRecieve(const char* err_msg) : HttpBaseException{err_msg} {}
    HttpFailedToRecieve(const HttpFailedToRecieve& http_failed_recieve) : HttpBaseException{http_failed_recieve} {}

    virtual ~HttpFailedToRecieve() {}
};

#endif //INSTAGRAM_CPP_HTTPFAILEDTORECIEVE_H
