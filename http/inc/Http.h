#ifndef HTTP_DEFINITIONS
#define HTTP_DEFINITIONS

#include <functional>
#include <string>
#include <cstring>

#define HTTP_1_1 "HTTP/1.1"
#define CRLF "\r\n"
#define ARG_START_DELIMETER '?'
#define ARG_DELIMETER '&'
#define ARG_EQUAL '='

namespace Http{
    enum class HttpProtocol{
        HTTP, HTTPS
    };

    enum class Method {
        UNKNOWN = -1, POST = 0, GET = 2, HEAD = 3, PUSH = 4, UPDATE = 5
    };

    const Method methods[] = {Method::POST, Method::GET, Method::PUSH, Method::UPDATE, Method::HEAD};

    enum class Header {
        UNKNOWN = -1, CONTENT_LENGTH = 0, CONTENT_TYPE = 1, USER_AGENT = 2, CONNECTION = 3, HOST = 4, ACCEPT = 5, CACHE_CONTROL = 6, SET_COOKIE = 7,
        CONTENT_LANGUAGE = 8, EXPIRES = 9, ACCEPT_ENCODING = 10, ACCEPT_LANGUAGE = 11, COOKIE  = 12, TRANSFER_ENCODING = 13, LOCATION = 14
    };

    const Header headers[] = {Header::CONTENT_LENGTH, Header::CONTENT_TYPE, Header::USER_AGENT, 
        Header::CONNECTION, Header::HOST, Header::ACCEPT, Header::CACHE_CONTROL, Header::SET_COOKIE,
        Header::CONTENT_LANGUAGE, Header::EXPIRES, Header::ACCEPT_ENCODING, Header::ACCEPT_LANGUAGE, 
        Header::COOKIE, Header::TRANSFER_ENCODING, Header::LOCATION
    };
    
    enum class Content_Type {
        FORM_DATA = 0
    };

    enum class Status{
        UNKNOWN = 0, OK = 200, MOVED = 302, BAD_REQUEST = 400, UNAUTHORIZED = 401, FORBIDDEN = 403, NOT_FOUND = 404, INTERNAL_SERVER_ERROR = 500
    };

    const Status statuses[] = {Status::OK, Status::MOVED, Status::BAD_REQUEST, Status::UNAUTHORIZED, Status::FORBIDDEN, Status::NOT_FOUND, Status::INTERNAL_SERVER_ERROR};

    const char* get_str(Method method);
    const char* get_str(Header header);
    const char* get_str(Content_Type content_type);
    const char* get_str(Status status);

    template <typename T> 
    T from_str(const char* str);

    template<typename T>
    T from_str(const std::string& str);
    
    Status from_int(int status);

    struct enum_hash{
        template <typename T>
        inline typename std::enable_if<std::is_enum<T>::value, std::size_t>::type
        operator ()(T const value) const{
            return static_cast<std::size_t>(value);
        }
    };
}

#endif
