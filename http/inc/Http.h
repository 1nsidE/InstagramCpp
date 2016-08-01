#ifndef HTTP_DEFINITIONS
#define HTTP_DEFINITIONS

#include <functional>
#include <string>
#include <cstring>
#include "Definitions.h"

namespace Http{
    enum class HttpProtocol{
        HTTP, HTTPS
    };

    enum class Method {
        UNKNOWN = -1, POST = 0, GET = 2, HEAD = 3, PUSH = 4, UPDATE = 5, DELETE = 6
    };

    enum class Header {
        UNKNOWN = -1, CONTENT_LENGTH = 0, CONTENT_TYPE = 1, USER_AGENT = 2, CONNECTION = 3, HOST = 4, ACCEPT = 5, CACHE_CONTROL = 6, SET_COOKIE = 7,
        CONTENT_LANGUAGE = 8, EXPIRES = 9, ACCEPT_ENCODING = 10, ACCEPT_LANGUAGE = 11, COOKIE  = 12, TRANSFER_ENCODING = 13, LOCATION = 14
    };

    enum  Status{
        UNKNOWN = -1, OK = 200, MOVED = 302, BAD_REQUEST = 400, UNAUTHORIZED = 401, FORBIDDEN = 403, NOT_FOUND = 404, INTERNAL_SERVER_ERROR = 500
    };

    const char* to_string(Method method) noexcept;
    const char* to_string(Header header) noexcept;
    const char* to_string(Status status) noexcept;

    std::string change_case(const char* str, bool to_upper = false);
    std::string change_case(const std::string& str, bool to_upper = false);

    Method from_str(const char* str);
    Method from_str(const std::string& str);
}

#endif
