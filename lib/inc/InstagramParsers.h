#include <string>
#include "results/MediaEntries.h"
#include "results/AuthorizationToken.h"
#include "results/UserInfo.h"
#include "results/UsersInfo.h"
#include "results/RelationshipInfo.h"
#include "results/TagInfo.h"
#include "results/TagsInfo.h"
#include "results/CommentsInfo.h"
#include "results/LocationsInfo.h"

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

    std::string getErrorMessage(const std::string& json);
}
