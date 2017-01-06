#ifndef HTTP_DEFINITIONS_HEADER
#define HTTP_DEFINITIONS_HEADER

#ifdef _WIN32
    #include<xstring>
    #include<unordered_map>
    #include<map>
    #include<vector>

    #ifdef HTTP_LIB_EXPORT
        #define EXPORT_HTTP __declspec(dllexport)
        #define HTTP_EXP_TMP
    #else
        #define EXPORT_HTTP __declspec(dllimport)
        #define HTTP_EXP_TMP extern
    #endif

    HTTP_EXP_TMP template class EXPORT_HTTP std::map<std::string, std::string>;
    HTTP_EXP_TMP template class EXPORT_HTTP std::unordered_map<std::string, std::string>;
    HTTP_EXP_TMP template struct EXPORT_HTTP std::pair<std::string, std::string>;
#endif

#ifdef __linux__
    #define EXPORT_HTTP
#endif

#define HTTP_1_1 "HTTP/1.1"
#define HTTP_PROTO "http"
#define HTTPS_PROTO "https"
#define HTTP_PROTO_DELIMETER "://"
#define CRLF "\r\n"
#define HEADER_SEPARATOR ": "
#define ARG_START_DELIMETER '?'
#define ARG_DELIMETER '&'
#define ARG_EQUAL '='

#endif

