#include <string>
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
    AuthorizationToken parseAuthToken(const std::string& json);
    MediaEntries parseMediaEntries(const std::string& json);
    MediaEntry parseMediaEntry(const std::string& json);
    UserInfo parseUserInfo(const std::string& json);
    UsersInfo parseUsersInfo(const std::string& json);
    RelationshipInfo parseRelationshipInfo(const std::string& json);
    TagInfo parseTagInfo(const std::string& json);
    TagsInfo parseTagsInfo(const std::string& json);
    CommentsInfo parseComments(const std::string& json);
    LocationInfo parseLocation(const std::string& json);
    LocationsInfo parseLocations(const std::string& json);

    std::string getError(const std::string& json);

}
