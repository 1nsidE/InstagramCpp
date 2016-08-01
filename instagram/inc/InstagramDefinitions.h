#ifdef WIN32
    #include<xstring>

    #ifdef INSTAGRAM_LIB_EXPORT
        #define EXPORT_INSTAGRAM __declspec(dllexport)
        #define EXPIMP_TEMPLATE
    #else
        #define EXPORT_INSTAGRAM __declspec(dllimport)
        #define EXPIMP_TEMPLATE extern
    #endif
#endif

#ifdef __linux__
#define EXPORT_INSTAGRAM
#define EXPIMP_TEMPLATE
#endif