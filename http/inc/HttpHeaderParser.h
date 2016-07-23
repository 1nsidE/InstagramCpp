#ifndef HTTP_HEADER_PARSER
#define HTTP_HEADER_PARSER

#include "HttpHeader.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include <memory>
#include <vector>

namespace Http{

    class HttpHeaderParser{
    public:
        static HttpResponse parse_response(const std::string &header);
        static HttpRequest parse_request(const std::string &header);
    private:
        static std::vector<std::string> tokenize(const std::string& str, const char delimeter, bool once = false);
        static void parse_headers(std::istringstream& string_stream, HttpHeader& header);
        static HttpUrl parse_url(const std::string& url);
        static std::string trim(const std::string& str);
    };

}
#endif
