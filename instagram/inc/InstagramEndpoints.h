//
// Created by inside on 4/6/16.
//

#ifndef HTTPSERVER_INSTAGRAMMETHODS_H
#define HTTPSERVER_INSTAGRAMMETHODS_H

namespace Instagram{
    static const char* GET_AUTH_CODE = "/oauth/access_token";
    
    static const char* USERS_SELF_RECENT_MEDIA = "/v1/users/self/media/recent";
    static const char* USERS_SEARCH = "/v1/users/search";
    static const char* USERS_SELF_LIKED = "/v1/users/self/media/like";
    static const char* USERS_SELF_INFO = "/v1/users/self";

    static const char* RELATIONSHIPS_FOLLOWS = "/v1/users/self/follows";
}

#endif //HTTPSERVER_INSTAGRAMMETHODS_H
