#include "UserInfo.h"

namespace Instagram {

UserInfo::UserInfo() {} 

UserInfo::UserInfo(const UserInfo& userInfo) : BaseResult{userInfo},
                                                m_id{userInfo.m_id},
                                                m_username{userInfo.m_username},
                                                m_name{userInfo.m_name},
                                                m_lastName{userInfo.m_lastName},
                                                m_bio{userInfo.m_bio},
                                                m_profPicUrl{userInfo.m_profPicUrl},
                                                m_website{userInfo.m_website},
                                                m_followedBy{userInfo.m_followedBy},
                                                m_follows{userInfo.m_follows},
                                                m_mediaCount{userInfo.m_mediaCount} {}

UserInfo::UserInfo(UserInfo&& userInfo) : BaseResult{std::forward<BaseResult>(userInfo)},
                                           m_id{std::move(userInfo.m_id)},
                                           m_username{std::move(userInfo.m_username)},
                                           m_name{std::move(userInfo.m_name)},
                                           m_lastName{std::move(userInfo.m_lastName)},
                                           m_bio{std::move(userInfo.m_bio)},
                                           m_profPicUrl{std::move(userInfo.m_profPicUrl)},
                                           m_website{std::move(userInfo.m_website)},
                                           m_followedBy{userInfo.m_followedBy},
                                           m_follows{userInfo.m_follows},
                                           m_mediaCount{userInfo.m_mediaCount} {

    userInfo.m_follows = -1;
    userInfo.m_followedBy = -1;
    userInfo.m_mediaCount = -1;
}


UserInfo::UserInfo(const char* errMsg) : BaseResult{errMsg} {}

UserInfo::UserInfo(const std::string& errMsg) : BaseResult{errMsg} {}

UserInfo::~UserInfo() {}

UserInfo& UserInfo::operator=(const UserInfo& userInfo) {
    if (this == &userInfo) {
        return *this;
   }

    BaseResult::operator=(userInfo);

    m_id = userInfo.m_id;
    m_username = userInfo.m_username;
    m_name = userInfo.m_name;
    m_lastName = userInfo.m_lastName;
    m_bio = userInfo.m_bio;
    m_profPicUrl = userInfo.m_profPicUrl;
    m_website = userInfo.m_website;

    m_followedBy = userInfo.m_followedBy;
    m_follows = userInfo.m_follows;
    m_mediaCount = userInfo.m_mediaCount;

    return *this;
}

UserInfo& UserInfo::operator=(UserInfo&& userInfo) {
    if (this == &userInfo) {
        return *this;
   }

    BaseResult::operator=(std::forward<BaseResult>(userInfo));

    m_id = std::move(userInfo.m_id);
    m_username = std::move(userInfo.m_username);
    m_name = std::move(userInfo.m_name);
    m_lastName = std::move(userInfo.m_lastName);
    m_bio = std::move(userInfo.m_bio);
    m_profPicUrl = std::move(userInfo.m_profPicUrl);
    m_website = std::move(userInfo.m_website);

    m_followedBy = userInfo.m_followedBy;
    userInfo.m_followedBy = -1;
    m_follows = userInfo.m_follows;
    userInfo.m_follows = -1;
    m_mediaCount = userInfo.m_mediaCount;
    userInfo.m_mediaCount = -1;

    return *this;
}

const std::string& UserInfo::id() const noexcept {
    return m_id;
}

const std::string& UserInfo::username() const noexcept {
    return m_username;
}

const std::string& UserInfo::lastName() const noexcept {
    return m_lastName;
}

const std::string& UserInfo::name() const noexcept {
    return m_name;
}

const std::string& UserInfo::bio() const noexcept {
    return m_bio;
}

const std::string& UserInfo::profilePictureUrl() const noexcept {
    return m_profPicUrl;
}

const std::string& UserInfo::website() const noexcept {
    return m_website;
}

int UserInfo::followedBy() const noexcept {
    return m_followedBy;
}

int UserInfo::follows() const noexcept {
    return m_follows;
}

int UserInfo::mediaCount() const noexcept {
    return m_mediaCount;
}

void UserInfo::setId(const std::string& id) {
    m_id = id;
}

void UserInfo::setUsername(const std::string& username) {
    m_username = username;
}

void UserInfo::setName(const std::string& name) {
    m_name = name;
}

void UserInfo::setLastName(const std::string& lastName) {
    m_lastName = lastName;
}

void UserInfo::setBio(const std::string& bio) {
    m_bio = bio;
}

void UserInfo::setProfilePictureUrl(const std::string& profPicUrl) {
    m_profPicUrl = profPicUrl;
}

void UserInfo::setWebsite(const std::string& website) {
    m_website = website;
}

void UserInfo::setFollowedBy(int count) {
    m_followedBy = count;
}

void UserInfo::setFollows(int count) {
    m_follows = count;
}

void UserInfo::setMediaCount(int count) {
    m_mediaCount = count;
}

}
