#ifndef INSTAGRAM_DEFINITIONS_HEADER
#define INSTAGRAM_DEFINITIONS_HEADER

#ifdef _WIN32
    #include<xstring>

    #ifdef INSTAGRAM_LIB_EXPORT
        #define EXPORT_INSTAGRAM __declspec(dllexport)
        #define INSTAGRAM_EXP_TMP
    #else
        #define EXPORT_INSTAGRAM __declspec(dllimport)
        #define INSTAGRAM_EXP_TMP extern
    #endif
#endif

#ifdef __linux__
    #define EXPORT_INSTAGRAM
#endif

#endif
