//
// Created by inside on 4/24/16.
//

#include "MediaEntry.h"

namespace Instagram {

MediaEntry::MediaEntry() : BaseResult{} {}

MediaEntry::MediaEntry(const std::string& errMsg) : BaseResult{errMsg} {}

MediaEntry::MediaEntry(const char* errMsg) : BaseResult{errMsg} {}

MediaEntry::MediaEntry(const MediaEntry &mediaEntry): BaseResult{mediaEntry},
                                                        m_link{mediaEntry.m_link},
                                                        m_id{mediaEntry.m_id},
                                                        m_caption{mediaEntry.m_caption},
                                                        m_lowResolution{mediaEntry.m_lowResolution},
                                                        m_thumbnail{mediaEntry.m_thumbnail},
                                                        m_standartResolution{mediaEntry.m_standartResolution},
                                                        m_filter{mediaEntry.m_filter},
                                                        m_videoLow{mediaEntry.m_videoLow},
                                                        m_videoStandart{mediaEntry.m_videoStandart},
                                                        m_tags{mediaEntry.m_tags},
                                                        m_users{mediaEntry.m_users},
                                                        m_userInfo{mediaEntry.m_userInfo},
                                                        m_commentsCount{mediaEntry.m_commentsCount},
                                                        m_likesCount{mediaEntry.m_likesCount},
                                                        m_createTime{mediaEntry.m_createTime},
                                                        m_mediaType{mediaEntry.m_mediaType} {}


MediaEntry::MediaEntry(MediaEntry &&mediaEntry) : MediaEntry(){
    swap(*this, mediaEntry);
}

MediaEntry::~MediaEntry() {}

MediaEntry& MediaEntry::operator=(const MediaEntry& mediaEntry) {
    MediaEntry copy{mediaEntry};

    swap(*this, copy);
    return *this;
}

MediaEntry& MediaEntry::operator=(MediaEntry&& mediaEntry) {
    swap(*this, mediaEntry);

    MediaEntry temp{};
    swap(mediaEntry, temp);

    return *this;
}

MediaType MediaEntry::type() const noexcept {
    return m_mediaType;
}

const std::string& MediaEntry::link() const noexcept {
    return m_link;
}

const std::string& MediaEntry::id() const noexcept {
    return m_id;
}

const std::string& MediaEntry::caption() const noexcept {
    return m_caption;
}

const std::vector<std::string>& MediaEntry::tags() const noexcept {
    return m_tags;
}

const std::vector<std::string>& MediaEntry::usersInPhoto() const noexcept {
    return m_users;
}

int MediaEntry::commentsCount() const  noexcept {
    return m_commentsCount;
}

int MediaEntry::likesCount() const noexcept {
    return m_likesCount;
}

long MediaEntry::createTime() const noexcept {
    return m_createTime;
}

const std::string& MediaEntry::standartResolution() const noexcept {
    return m_standartResolution;
}

const std::string& MediaEntry::thumbnail() const noexcept {
    return m_thumbnail;
}

const std::string& MediaEntry::lowResolution() const noexcept {
    return m_lowResolution;
}

const std::string& MediaEntry::filter() const noexcept {
    return m_filter;
}

const std::string& MediaEntry::videoLowResolution() const noexcept {
    return m_videoLow;
}

const std::string& MediaEntry::videoStandartResolution() const noexcept {
    return m_videoStandart;
}

const UserInfo& MediaEntry::userInfo() const noexcept{
    return m_userInfo;
}

void MediaEntry::setType(MediaType type) {
    m_mediaType = type;
}

void MediaEntry::setLink(const std::string& _m_link) {
    m_link = _m_link;
}

void MediaEntry::setId(const std::string& id) {
    m_id = id;
}

void MediaEntry::setCaption(const std::string& caption) {
    m_caption = caption;
}

void MediaEntry::addTag(const std::string &tag) {
    m_tags.push_back(tag);
}

void MediaEntry::setCommentsCount(int count) {
    m_commentsCount = count;
}

void MediaEntry::setLikeCount(int count) {
    m_likesCount = count;
}

void MediaEntry::setCreateTime(long time) {
    m_createTime = time;
}

void MediaEntry::setStandartResolution(const std::string& url) {
    m_standartResolution = url;
}

void MediaEntry::setThumbnail(const std::string& url) {
    m_thumbnail = url;
}

void MediaEntry::setLowResolution(const std::string& url) {
    m_lowResolution = url;
}

void MediaEntry::setFilter(const std::string& _m_filter) {
    m_filter = _m_filter;
}

void MediaEntry::setVideoLowResolution(const std::string& url) {
    m_videoLow = url;
}

void MediaEntry::setVideoStandartResolution(const std::string& url) {
    m_videoStandart = url;
}

void MediaEntry::addUser(const std::string& user) {
    m_users.push_back(user);
}

void MediaEntry::setUserInfo(const UserInfo& userInfo){
    m_userInfo = userInfo;
}

void MediaEntry::setUserInfo(UserInfo&& userInfo){
    using std::swap;
    swap(m_userInfo, userInfo);
    
    UserInfo temp{};
    swap(userInfo, temp);
}

void swap(MediaEntry& media1, MediaEntry& media2){
    using std::swap;

    swap(static_cast<BaseResult&>(media1), static_cast<BaseResult&>(media2));

    swap(media1.m_link, media2.m_link);
    swap(media1.m_id, media2.m_id);
    swap(media1.m_caption, media2.m_caption);
    swap(media1.m_lowResolution, media2.m_lowResolution);
    swap(media1.m_thumbnail, media2.m_thumbnail);
    swap(media1.m_standartResolution, media2.m_standartResolution);
    swap(media1.m_filter, media2.m_filter);
    swap(media1.m_videoLow, media2.m_videoLow);
    swap(media1.m_videoStandart, media2.m_videoStandart);
    swap(media1.m_tags, media2.m_tags);
    swap(media1.m_users, media2.m_users);
    swap(media1.m_userInfo, media2.m_userInfo);
    swap(media1.m_commentsCount, media2.m_commentsCount);
    swap(media1.m_likesCount, media2.m_likesCount);
    swap(media1.m_createTime, media2.m_createTime);
    swap(media1.m_mediaType, media2.m_mediaType);
}

}
