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

#include "InstagramDefinitions.h"

namespace Instagram{

class EXPORT_INSTAGRAM InstagramClient{
public:
    InstagramClient();
    InstagramClient(const std::string& authToken);
    InstagramClient(InstagramClient& instServ) = delete;
    InstagramClient(InstagramClient&& instServ) = delete;

    void setAuthToken(const std::string& authToken);
    const std::string& getAuthToken() const;

//API's
    AuthorizationToken authenticate(const std::string& code,
                                     const std::string& clientId,
                                     const std::string& clientSecret,
                                     const std::string& redirectUri);
//Users
    UserInfo getUserInfo();
    UserInfo getUserInfo(const std::string& userId);
    MediaEntries getRecentMedia(unsigned count = 20);
    MediaEntries getRecentMedia(const std::string& minId, const std::string& maxId, unsigned count = 20);
    MediaEntries getRecentMedia(const std::string& userId, const std::string& minId, const std::string& maxId, unsigned count = 20);
    MediaEntries getRecentMedia(const std::string& userId, unsigned count = 20);
    MediaEntries getLikedMedia(unsigned int count = 20);
    MediaEntries getLikedMedia(const std::string& maxId, unsigned int count = 20);
    UsersInfo searchUsers(const std::string& query, unsigned count = 20);
//Relationships
    UsersInfo getFollows();
    UsersInfo getFollowedBy();
    UsersInfo getRequestedBy();
    RelationshipInfo getRelationshipInfo(const std::string& userId);
    RelationshipInfo follow(const std::string& userId);
    RelationshipInfo unfollow(const std::string& userId);
    RelationshipInfo approve(const std::string& userId);
    RelationshipInfo ignore(const std::string& userId);
//Media
    MediaEntry getMedia(const std::string& mediaId);
    MediaEntry getMediaWithShortCode(const std::string& shortcode);
    MediaEntries searchMedia(double lat, double lng, int distance = 1000);
//Comments
    CommentsInfo getComments(const std::string& mediaId);
    BaseResult comment(const std::string& mediaId, const std::string& text);
    BaseResult deleteComment(const std::string& mediaId, const std::string& commentId);
//Likes
    UsersInfo getLikes(const std::string& mediaId);
    BaseResult like(const std::string& mediaId);
    BaseResult unlike(const std::string& mediaId);
//Tags
    TagInfo getTagInfo(const std::string& tagName);
    TagsInfo searchTags(const std::string& query);
    MediaEntries getRecentMediaForTag(const std::string& tagName);
//Locations
    LocationInfo getLocationById(const std::string& locationId);
    MediaEntries getMediaForLoccation(const std::string& locationId);
    LocationsInfo searchLocations(double lat, double lng, int distance = 500);
private:
    Http::HttpClient m_httpClient;
    std::string m_authToken;

    UsersInfo getUsersInfo(const Http::HttpUrl& url);
    MediaEntries getMedia(const Http::HttpUrl& url);

    enum class Relationship{follow, unfollow, approve, ignore};
    RelationshipInfo postRelationship(Relationship relationship, const std::string& userId);

    bool checkAuth();
    std::string getResult(const Http::HttpResponse& response);
};

}

#endif
