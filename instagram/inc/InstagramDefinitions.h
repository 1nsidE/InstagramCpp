#ifndef INSTAGRAM_DEFINITIONS_HEADER
#define INSTAGRAM_DEFINITIONS_HEADER

#ifdef WIN32
    #include<xstring>

    #ifdef INSTAGRAM_LIB_EXPORT
        #define EXPORT_INSTAGRAM __declspec(dllexport)
        #define INSTAGRAM_EXP_TMP
    #else
        #define EXPORT_INSTAGRAM __declspec(dllimport)
        #define INSTAGRAM_EXP_TMP extern
    #endif

    INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM std::vector<std::string>;
    INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM std::vector<MediaEntry>;
    INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM std::vector<UserInfo>;
    INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM std::vector<TagInfo>;
    INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM std::vector<CommentInfo>;
    INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM std::vector<LocationInfo>;

#endif

#ifdef __linux__
#define EXPORT_INSTAGRAM
#define EXPIMP_TEMPLATE
#endif

#endif
