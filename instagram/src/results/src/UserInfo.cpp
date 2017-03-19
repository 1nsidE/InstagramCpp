#include "UserInfo.h"

namespace Instagram {

UserInfo::UserInfo() {} 

UserInfo::UserInfo(const UserInfo& userInfo) : BaseResult{userInfo},
                                                m_id{userInfo.m_id},
                                                m_username{userInfo.m_username},
                                                m_fullName{userInfo.m_fullName},
                                                m_bio{userInfo.m_bio},
                                                m_profPicUrl{userInfo.m_profPicUrl},
                                                m_website{userInfo.m_website},
                                                m_followedBy{userInfo.m_followedBy},
                                                m_follows{userInfo.m_follows},
                                                m_mediaCount{userInfo.m_mediaCount} {}

UserInfo::UserInfo(UserInfo&& userInfo) : UserInfo(){
    swap(*this, userInfo);
}

UserInfo::UserInfo(const char* errMsg) : BaseResult{errMsg} {}

UserInfo::UserInfo(const std::string& errMsg) : BaseResult{errMsg} {}

UserInfo::~UserInfo() {}

UserInfo& UserInfo::operator=(const UserInfo& userInfo) {
    UserInfo copy{userInfo};

    swap(*this, copy);
    return *this;
}

UserInfo& UserInfo::operator=(UserInfo&& userInfo) {
    swap(*this, userInfo);

    UserInfo temp{};
    swap(userInfo, temp);
    return *this;
}

const std::string& UserInfo::id() const noexcept {
    return m_id;
}

const std::string& UserInfo::username() const noexcept {
    return m_username;
}


const std::string& UserInfo::fullName() const noexcept {
    return m_fullName;
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

void UserInfo::setFullName(const std::string& name) {
    m_fullName = name;
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

void swap(UserInfo& info1, UserInfo& info2){
    using std::swap;
    swap(static_cast<BaseResult&>(info1), static_cast<BaseResult&>(info2));

    swap(info1.m_id, info2.m_id);
    swap(info1.m_username, info2.m_username);
    swap(info1.m_fullName, info2.m_fullName);
    swap(info1.m_bio, info2.m_bio);
    swap(info1.m_profPicUrl, info2.m_profPicUrl);
    swap(info1.m_website, info2.m_website);
    swap(info1.m_followedBy, info2.m_followedBy);
    swap(info1.m_follows, info2.m_follows);
    swap(info1.m_mediaCount, info2.m_mediaCount);
}

}
