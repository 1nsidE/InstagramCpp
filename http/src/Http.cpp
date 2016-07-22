#include <cstring>
#include <unordered_map>
#include <algorithm>
#include "Http.h"

namespace Http{
    
    std::string change_case(const char* str, bool to_upper){
        std::string result{str};

        std::transform(result.begin(), result.end(), result.begin(), to_upper ? ::toupper : ::tolower);
        return result;  
    }
    
    std::string change_case(const std::string& str, bool to_upper) {
        std::string result{str};
        std::transform(result.begin(), result.end(), result.begin(), to_upper ? ::toupper : ::tolower);

        return result;
    }
    
    const char* to_string(Method method) noexcept{
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
            case Method::DELETE:
                return "DELETE";
            default:
                return "UNKNOWN";
        }
    }

    const char* to_string(Header header) noexcept{
        switch(header){
            case Header::CONTENT_LENGTH:
                return "content-length";
            case Header::CONTENT_TYPE:
                return "content-type";
            case Header::USER_AGENT:
                return "user-agent";
            case Header::CONNECTION:
                return "connection";
            case Header::HOST:
                return "host";
            case Header::ACCEPT:
                return "accept";
            case Header::CACHE_CONTROL:
                return "cache-control";
            case Header::SET_COOKIE:
                return "set-cookie";
            case Header::EXPIRES:
                return "expires";
            case Header::ACCEPT_ENCODING:
                return "accept-encoding";
            case Header::ACCEPT_LANGUAGE:
                return "accept-language";
            case Header::CONTENT_LANGUAGE:
                return "content-language";
            case Header::COOKIE:
                return "cookie";
            case Header::TRANSFER_ENCODING:
                return "transfer-encoding";
            case Header::LOCATION:
                return "location";
            default:
                return "unknown";
        }
    }

    const char* to_string(Status status) noexcept{
        switch(status){
            case Status::OK:
                return "OK";
            case Status::BAD_REQUEST:
                return "BAD REQUEST";
            case Status::UNAUTHORIZED:
                return "UNAUTHORIZED";
            case Status::FORBIDDEN:
                return "FORBIDDEN";
            case Status::INTERNAL_SERVER_ERROR:
                return "INTERNAL_SERVER_ERROR";
            case Status::NOT_FOUND:
                return "NOT FOUND";
            case Status::MOVED:
                return "MOVED";
            default:
                return "UNKNOWN";
        }
    }
    
    Status from_int(int _status){
        Status status = static_cast<Status>(_status);
        switch (status){
            case Status::BAD_REQUEST:
            case Status::FORBIDDEN:
            case Status::INTERNAL_SERVER_ERROR:
            case Status::MOVED:
            case Status::NOT_FOUND:
            case Status::OK:
            case Status::UNAUTHORIZED:
                return status;
            default:
                return Status::UNKNOWN;
        }
    }

    Method from_str(const char* str){
       const static std::unordered_map<std::string, Method> map{
            {"POST", Method::POST},
            {"GET", Method::GET},
            {"HEAD", Method::HEAD},
            {"PUSH", Method::PUSH},
            {"UPDATE", Method::UPDATE},
            {"DELETE", Method::DELETE}
        };

        std::string method = change_case(str, true);
        if(map.count(method)){
            return map.at(method);
        }else{
            return Method::UNKNOWN;
        }
    }

    Method from_str(const std::string& str){
        return from_str(str.c_str());
    }
}

