//
// Created by inside on 4/6/16.
//

#ifndef HTTPSERVER_INSTAGRAMMETHODS_H
#define HTTPSERVER_INSTAGRAMMETHODS_H

namespace Instagram{
    namespace Users{
        static const char* users = "/v1/users/";
        static const char* recent_media = "/media/recent";
        static const char* search = "search";
        static const char* self_liked = "self/media/liked";
    }

    namespace Relationships{
        static const char* users = "/v1/users/";
        static const char* follows  = "self/follows";
        static const char* followed_by = "self/followed-by";
        static const char* requested_by = "self/requested-by";
        static const char* relationship = "/relationship/";
    }

    namespace Media{
        static const char* get_media = "/v1/media/";
        static const char* get_media_shortcode = "/v1/media/shortcode/";
        static const char* media_search = "/v1/media/search/";

    }

    namespace Comments{
        static const char* TEXT_ARG = "text";

        static const char* media = "/v1/media/";
        static const char* comments = "/comments/";
    }

    namespace Likes{
        static const char* media = "/v1/media/";
        static const char* likes = "/likes";
    }

    namespace Tags{
        static const char* tags = "/v1/tags/";
        static const char* tags_search = "search/";
        static const char* recent_media = "/media/recent/";
    }

    namespace Locations{
        static const char* locations = "/v1/locations/";
        static const char* recent_media = "/media/recent/";
        static const char* search = "search/";
    }
}


#endif //HTTPSERVER_INSTAGRAMMETHODS_H
