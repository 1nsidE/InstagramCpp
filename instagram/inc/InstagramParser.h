#include <string>
#include <json/json.h>
#include "MediaEntries.h"
#include "AuthorizationToken.h"
#include "UserInfo.h"
#include "UsersInfo.h"
#include "RelationshipInfo.h"
#include "TagInfo.h"
#include "TagsInfo.h"
#include "CommentsInfo.h"
#include "LocationsInfo.h"

namespace Instagram{

class InstagramParser{
public:
    InstagramParser();
    InstagramParser(const InstagramParser& instagram_parser) = delete;
    InstagramParser(InstagramParser&& instagram_parser) = delete;

    AuthorizationToken parse_auth_token(const std::string& json);
    MediaEntries parse_media_entries(const std::string& json);
    MediaEntry parse_media_entry(const std::string& json);
    UserInfo parse_user_info(const std::string& json);
    UsersInfo parse_users_info(const std::string& json);
    RelationshipInfo parse_relationship_info(const std::string& json);
    TagInfo parse_tag_info(const std::string& json);
    TagsInfo parse_tags_info(const std::string& json);
    CommentsInfo parse_comments(const std::string& json);
    LocationInfo parse_location(const std::string& json);
    LocationsInfo parse_locations(const std::string& json);

    std::string get_error(const std::string& json);
private:
    MediaEntry get_media_entry(const Json::Value& media);
    UserInfo get_user_info(const Json::Value& info);
    CommentInfo get_comment_info(const Json::Value& comment);
    LocationInfo get_location(const Json::Value& locations);
    Json::Reader reader;
};

}
