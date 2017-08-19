#ifndef INSTAGRAM_SERVICE
#define INSTAGRAM_SERVICE

#include "http/HttpClient.h"

#include "results/AuthorizationToken.h"
#include "results/MediaEntries.h"
#include "results/UsersInfo.h"
#include "results/RelationshipInfo.h"
#include "results/TagsInfo.h"
#include "results/CommentsInfo.h"
#include "results/LocationsInfo.h"

#include "InstagramDefinitions.h"

namespace Instagram{

class EXPORT_INSTAGRAM InstagramClient{
public:
    InstagramClient();
    InstagramClient(const std::string& authToken);
    InstagramClient(InstagramClient& instServ) = delete;
    InstagramClient(InstagramClient&& instServ);

    InstagramClient& operator=(InstagramClient&& client);

    void setAuthToken(const std::string& authToken);
    const std::string& getAuthToken() const;

//API's
    AuthorizationToken authenticate(const std::string& code,
                                     const std::string& clientId,
                                     const std::string& clientSecret,
                                     const std::string& redirectUri);
//Users
    UserInfo getUserInfo() const;
    UserInfo getUserInfo(const std::string& userId) const;
    MediaEntries getRecentMedia(unsigned count = 20) const;
    MediaEntries getRecentMedia(const std::string& minId, const std::string& maxId, unsigned count = 20) const;
    MediaEntries getRecentMedia(const std::string& userId, const std::string& minId, const std::string& maxId, unsigned count = 20) const;
    MediaEntries getRecentMedia(const std::string& userId, unsigned count = 20) const;
    MediaEntries getLikedMedia(unsigned int count = 20) const;
    MediaEntries getLikedMedia(const std::string& maxId, unsigned int count = 20)const;
    UsersInfo searchUsers(const std::string& query, unsigned count = 20) const;
//Relationships
    UsersInfo getFollows() const;
    UsersInfo getFollowedBy() const;
    UsersInfo getRequestedBy() const;
    RelationshipInfo getRelationshipInfo(const std::string& userId) const;
    RelationshipInfo follow(const std::string& userId);
    RelationshipInfo unfollow(const std::string& userId);
    RelationshipInfo approve(const std::string& userId);
    RelationshipInfo ignore(const std::string& userId);
//Media
    MediaEntry getMedia(const std::string& mediaId) const;
    MediaEntry getMediaWithShortCode(const std::string& shortcode) const;
    MediaEntries searchMedia(double lat, double lng, int distance = 1000) const;
//Comments
    CommentsInfo getComments(const std::string& mediaId) const;
    BaseResult comment(const std::string& mediaId, const std::string& text);
    BaseResult deleteComment(const std::string& mediaId, const std::string& commentId);
//Likes
    UsersInfo getLikes(const std::string& mediaId) const;
    BaseResult like(const std::string& mediaId);
    BaseResult unlike(const std::string& mediaId);
//Tags
    TagInfo getTagInfo(const std::string& tagName) const;
    TagsInfo searchTags(const std::string& query) const;
    MediaEntries getRecentMediaForTag(const std::string& tagName) const;
//Locations
    LocationInfo getLocationById(const std::string& locationId) const;
    MediaEntries getMediaForLocation(const std::string& locationId) const;
    LocationsInfo searchLocations(double lat, double lng, int distance = 500) const;
private:
    mutable Http::HttpClient m_httpClient;
    std::string m_authToken;

    UsersInfo getUsersInfo(const Http::HttpUrl& url) const;
    MediaEntries getMedia(const Http::HttpUrl& url) const;

    enum class Relationship{follow, unfollow, approve, ignore};
    RelationshipInfo postRelationship(Relationship relationship, const std::string& userId);

    bool checkAuth() const;
    std::string getResult(const Http::HttpResponse& response) const;

    friend void swap(InstagramClient& first, InstagramClient& second);
};

}

#endif
