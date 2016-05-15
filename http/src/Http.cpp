#include <cstring>
#include <easylogging/easylogging++.h>
#include "Http.h"

namespace Http{

    const char* get_str(Method method){
        switch(method){
            case Method::POST:
                return "POST";
            case Method::GET:
                return "GET";
            case Method::PUSH:
                return "PUSH";
            case Method::UPDATE:
                return "UPDATE";
            case Method::HEAD:
                return "HEAD";
            default:
                return "UNKNOWN";
        }
    }

    const char* get_str(Header header){
        switch(header){
            case Header::CONTENT_LENGTH:
                return "Content-Length: ";
            case Header::CONTENT_TYPE:
                return "Content-Type: ";
            case Header::USER_AGENT:
                return "User-Agent: ";
            case Header::CONNECTION:
                return "Connection: ";
            case Header::HOST:
                return "Host: ";
            case Header::ACCEPT:
                return "Accept: ";
            case Header::CACHE_CONTROL:
                return "Cache-Control: ";
            case Header::SET_COOKIE:
                return "Set-Cookie: ";
            case Header::EXPIRES:
                return "Expires: ";
            case Header::ACCEPT_ENCODING:
                return "Accept-Encoding: ";
            case Header::ACCEPT_LANGUAGE:
                return "Accept-Language: ";
            case Header::CONTENT_LANGUAGE:
                return "Content-Language: ";
            default:
                return "Unknown";
        }
    }

    const char* get_str(Content_Type content_type){
        switch(content_type){
        case Content_Type::FORM_DATA:
            return "multipart/form-data";
        }

        return "Unknown";
    }

    const char* get_str(Status status){
        switch(status){
            case Status::OK:
                return "OK";
            case Status::BAD_REQUEST:
                return "Bad Request";
            case Status::UNAUTHORIZED:
                return "Unauthorized";
            case Status::FORBIDDEN:
                return "Forbidden";
            case Status::INTERNAL_SERVER_ERROR:
                return "Internal Server Error";
            case Status::NOT_FOUND:
                return "Not Found";
            default:
                return "Unknown";
        }
    }

    Status from_int(int _status){
        for(Status status : statuses){
            if(static_cast<int>(status) == _status){
                return status;
            }
        }

//        LOG(INFO) << "Unknown status received : " << _status;
        return Status::UNKNOWN;
    }

    template<>
    Header from_str<Header>(const char* str){
         for(Header header : headers){
            if(!(std::strncmp(str, get_str(header), std::strlen(str)))){
                return header;
            }
        } 

//        LOG(INFO) << "Unknown header received : " << str;
        return Header::UNKNOWN;
    }

    template<>
    Status from_str<Status>(const char* str){
        for(Status status : statuses){
            if(!std::strcmp(str, get_str(status))){
                return status;
            }
        }

//        LOG(INFO) << "Unknown status received : " << str;
        return Status::UNKNOWN;
    }

    template<>
    Method from_str<Method>(const char* str){
        for(Method method : methods){
            if(!std::strcmp(str, get_str(method))){
                return method;
            }
        }

//        LOG(INFO) << "Unknown method received : " << str;
        return Method::UNKNOWN;        
    }

    template<>
    Header from_str<Header>(const std::string& str){
        return from_str<Header>(str.c_str());
    }

    template<>
    Status from_str<Status>(const std::string& str){
        return from_str<Status>(str.c_str());
    }

    template<>
    Method from_str<Method>(const std::string& str){
        return from_str<Method>(str.c_str());
    }
}
