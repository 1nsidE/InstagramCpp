//
// Created by inside on 7/3/16.
//

#include "CommentInfo.h"

namespace Instagram {

CommentInfo::CommentInfo() : BaseResult{} {}

CommentInfo::CommentInfo(const std::string& text, const std::string& id, long createTime, const UserInfo& userInfo) : BaseResult{}, m_text{text}, m_id{id}, m_createTime{createTime}, m_userInfo{userInfo} {}

CommentInfo::CommentInfo(const CommentInfo& commentInfo) : BaseResult{commentInfo}, m_text{commentInfo.m_text}, m_id{commentInfo.m_id}, m_createTime{commentInfo.m_createTime}, m_userInfo{commentInfo.m_userInfo} {}

CommentInfo::CommentInfo(CommentInfo&& commentInfo) : CommentInfo(){
    swap(*this, commentInfo);
}

CommentInfo::CommentInfo(const std::string& errMsg) : BaseResult{errMsg} {}

CommentInfo::CommentInfo(const char* errMsg) : BaseResult{errMsg} {}

CommentInfo::~CommentInfo() {}

CommentInfo& CommentInfo::operator=(const CommentInfo& commentInfo) {
    CommentInfo copy{commentInfo};

    swap(*this, copy);
    return *this;
}

CommentInfo& CommentInfo::operator=(CommentInfo&& commentInfo) {
    swap(*this, commentInfo);

    CommentInfo temp{};
    swap(commentInfo, temp);
    return *this;
}

const std::string& CommentInfo::text() const noexcept {
    return m_text;
}

const std::string& CommentInfo::id() const noexcept {
    return m_id;
}

long CommentInfo::createTime() const noexcept {
    return m_createTime;
}

const UserInfo& CommentInfo::userInfo() const noexcept {
    return m_userInfo;
}

void CommentInfo::setText(const std::string &text) {
    m_text = text;
}

void CommentInfo::setId(const std::string &id) {
    m_id = id;
}

void CommentInfo::setCreateTime(long create_time_) {
    m_createTime = create_time_;
}

void CommentInfo::setUserInfo(const UserInfo &userInfo) {
    m_userInfo = userInfo;
}

void CommentInfo::setUserInfo(UserInfo&& userInfo){
    swap(m_userInfo, userInfo);

    UserInfo temp{};
    swap(userInfo, temp);
}

void swap(CommentInfo& first, CommentInfo& second){
    using std::swap;
    swap(static_cast<BaseResult&>(first), static_cast<BaseResult&>(second));

    swap(first.m_text, second.m_text);
    swap(first.m_id, second.m_id);
    swap(first.m_createTime, second.m_createTime);
    swap(first.m_userInfo, second.m_userInfo);
}

}
