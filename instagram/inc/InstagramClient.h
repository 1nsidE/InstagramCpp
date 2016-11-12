#ifndef INSTAGRAM_SERVICE
#define INSTAGRAM_SERVICE

#include "HttpResponse.h"
#include "HttpRequest.h"
#include "HttpClient.h"
#include "HttpUrl.h"

#include "AuthorizationToken.h"
#include "MediaEntries.h"
#include "UsersInfo.h"
#include "RelationshipInfo.h"
#include "TagsInfo.h"
#include "CommentsInfo.h"
#include "LocationsInfo.h"

#include "InstagramParser.h"
#include "InstagramDefinitions.h"

namespace Instagram{

class EXPORT_INSTAGRAM InstagramClient{
public:
    InstagramClient();
    InstagramClient(const std::string& _auth_token);
    InstagramClient(InstagramClient& inst_serv) = delete;
    InstagramClient(InstagramClient&& inst_serv) = delete;

    void set_auth_token(const std::string& _auth_token);
    const std::string& get_auth_token() const;

//API's
    AuthorizationToken exchange_code(const std::string& code,
                                     const std::string& client_id,
                                     const std::string& client_secret,
                                     const std::string& redirect_uri);
//Users
    UserInfo get_user_info();
    UserInfo get_user_info(const std::string& user_id);
    MediaEntries get_recent_media(unsigned count = 20);
    MediaEntries get_recent_media(const std::string& min_id, const std::string& max_id, unsigned count = 20);
    MediaEntries get_recent_media(const std::string& user_id, const std::string& min_id, const std::string& max_id, unsigned count = 20);
    MediaEntries get_recent_media(const std::string& user_id, unsigned count = 20);
    MediaEntries get_liked_media();
    MediaEntries get_liked_media(const std::string& max_id);
    UsersInfo search_users(const std::string& query, unsigned count = 20);
//Relationships
    UsersInfo get_follows();
    UsersInfo get_followed_by();
    UsersInfo get_requested_by();
    RelationshipInfo get_relationship_info(const std::string& user_id);
//Media
    MediaEntry get_media(const std::string& media_id);
    MediaEntry get_media_short(const std::string& shortcode);
    MediaEntries search_media(double lat, double lng, int distance = 1000);
//Comments
    CommentsInfo get_comments(const std::string& media_id);
    BaseResult comment(const std::string& media_id, const std::string& text);
    BaseResult delete_comment(const std::string& media_id, const std::string& comment_id);
//Likes
    UsersInfo get_likes(const std::string& media_id);
    BaseResult like(const std::string& media_id);
    BaseResult unlike(const std::string& media_id);
//Tags
    TagInfo get_tag_info(const std::string& tag_name);
    TagsInfo search_tags(const std::string& query);
    MediaEntries get_recent_media_tag(const std::string& tag_name);
//Locations
    LocationInfo get_location(const std::string& location_id);
    MediaEntries get_media_loc(const std::string& location_id);
    LocationsInfo search_locations(double lat, double lng, int distance = 500);
private:
    InstagramParser parser;
    Http::HttpClient http_client;
    std::string auth_token;

    UsersInfo get_users_info(const Http::HttpUrl& url);
    MediaEntries get_media(const Http::HttpUrl& url);

    void check_auth();
    std::string get_result(const Http::HttpResponse& response);
};


}

#endif
