//
// Created by inside on 4/6/16.
//

#ifndef HTTPSERVER_INSTAGRAMMETHODS_H
#define HTTPSERVER_INSTAGRAMMETHODS_H

namespace Instagram{
    
    namespace Auth{
        static const char* GET_AUTH_CODE = "/oauth/access_token";
    }
    
    namespace Users{
        static const char* users = "/v1/users/";
        static const char* search = "search";
        static const char* ownLikes = "self/media/liked";
    }

    namespace Relationships{
        static const char* follows  = "self/follows";
        static const char* followedBy = "self/followed-by";
        static const char* requestedBy = "self/requested-by";
        static const char* relationship = "/relationship/";
    }

    namespace Media{
        static const char* media = "/v1/media/";
        static const char* recentMedia = "/media/recent";
        static const char* byShortCode = "/v1/media/shortcode/";
        static const char* search = "/v1/media/search/";

    }

    namespace Comments{
        static const char* TEXT_ARG = "text";
        static const char* comments = "/comments/";
    }

    namespace Likes{
        static const char* likes = "/likes";
    }

    namespace Tags{
        static const char* tags = "/v1/tags/";
        static const char* tagsSearch = "search/";
    }

    namespace Locations{
        static const char* locations = "/v1/locations/";
        static const char* search = "search/";
    }
}


#endif //HTTPSERVER_INSTAGRAMMETHODS_H
