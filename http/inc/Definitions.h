#ifdef WIN32
    #include<xstring>
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
    #define EXPIMP_TEMPLATE
#endif

#define HTTP_1_1 "HTTP/1.1"
#define CRLF "\r\n"
#define HEADER_SEPARATOR ": "
#define ARG_START_DELIMETER '?'
#define ARG_DELIMETER '&'
#define ARG_EQUAL '='