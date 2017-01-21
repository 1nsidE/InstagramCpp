#ifndef HTTP_DEFINITIONS_HEADER
#define HTTP_DEFINITIONS_HEADER

#ifdef _WIN32
	#undef max
	#undef DELETE

    #ifdef HTTP_LIB_EXPORT
        #define EXPORT_HTTP __declspec(dllexport)
        #define HTTP_EXP_TMP
    #else
        #define EXPORT_HTTP __declspec(dllimport)
        #define HTTP_EXP_TMP extern
    #endif
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

