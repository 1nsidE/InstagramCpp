//
// Created by inside on 6/17/16.
//

#ifndef INSTAGRAM_CPP_HTTPBASEEXCEPTION_H
#define INSTAGRAM_CPP_HTTPBASEEXCEPTION_H

#include <stdexcept>

struct HttpBaseException : public std::runtime_error{
public:
    HttpBaseException(const std::string &err_msg) : runtime_error{err_msg} { }
    HttpBaseException(const char* err_msg) : runtime_error{err_msg} {}
    HttpBaseException(const HttpBaseException& http_err) : runtime_error{http_err} {}

    virtual ~HttpBaseException(){}
};

#endif //INSTAGRAM_CPP_HTTPBASEEXCEPTION_H
