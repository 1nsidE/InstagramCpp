#include <cstring>
#include <map>
#include <algorithm>
#include "Http.h"

namespace Http{
    
    const std::string change_case(const char* str, bool to_upper){
        std::string result{str};

        std::transform(result.begin(), result.end(), result.begin(), to_upper ? ::toupper : ::tolower);
        return result;  
    }

    const std::string change_case(const std::string& str, bool to_upper){
        std::string result{str};
        std::transform(result.begin(), result.end(), result.begin(), to_upper ? ::toupper : ::tolower);
        return result;
    }

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
            case Header::COOKIE:
                return "Cookie: ";
            case Header::TRANSFER_ENCODING:
                return "Transfer-Encoding: ";
            case Header::LOCATION:
                return "Location: ";
            default:
                return "Unknown: ";
        }
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
            case Status::MOVED:
                return "Moved";
            default:
                return "Unknown";
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
   
    template<>
    Header from_str<Header>(const char* str){
        const static std::map<std::string, Header> map{
            {"content-length", Header::CONTENT_LENGTH},
            {"content-type", Header::CONTENT_TYPE},
            {"user-agent", Header::USER_AGENT},
            {"connection", Header::CONNECTION},
            {"host", Header::HOST},
            {"accept", Header::ACCEPT},
            {"cache-control", Header::CACHE_CONTROL},
            {"set-cookie", Header::SET_COOKIE},
            {"content-language", Header::CONTENT_LANGUAGE},
            {"expires", Header::EXPIRES},
            {"accept-encoding", Header::ACCEPT_ENCODING},
            {"accept-language", Header::ACCEPT_LANGUAGE},
            {"cookie", Header::COOKIE},
            {"transfer-encoding", Header::TRANSFER_ENCODING},
            {"location", Header::LOCATION}
        };
        
        std::string header = change_case(str, false);

        if(map.count(header)){
            return map.at(header);
        } else {
            return Header::UNKNOWN;   
        }
    }

    template<>
    Header from_str<Header>(const std::string& str){
        return from_str<Header>(str.c_str());
    }

    template<>
    Status from_str<Status>(const char* str){
        const static std::map<std::string, Status> map{
            {"OK", Status::OK},
            {"MOVED", Status::MOVED},
            {"BAD REQUEST", Status::BAD_REQUEST},
            {"UNAUTHORIZED", Status::UNAUTHORIZED},
            {"FORBIDDEN", Status::FORBIDDEN},
            {"NOT FOUND", Status::NOT_FOUND},
            {"INTERNAL SERVER ERROR", Status::INTERNAL_SERVER_ERROR}
        };
        
        std::string status  = change_case(str, true);
        if(map.count(status)){
            return map.at(status);
        } else {
            return Status::UNKNOWN;
        }
    }

    template<>
    Status from_str<Status>(const std::string& str){
        return from_str<Status>(str.c_str());
    }


    template<>
    Method from_str<Method>(const char* str){
        const static std::map<std::string, Method> map{
            {"POST", Method::POST},
            {"GET", Method::GET},
            {"PUSH", Method::PUSH},
            {"UPDATE", Method::UPDATE},
            {"HEAD", Method::HEAD}
        };

        std::string method = change_case(str, true);
        if(map.count(method)){
            return map.at(method);
        }else{
            return Method::UNKNOWN;
        }
    }

    template<>
    Method from_str<Method>(const std::string& str){
        return from_str<Method>(str.c_str());
    }
}
