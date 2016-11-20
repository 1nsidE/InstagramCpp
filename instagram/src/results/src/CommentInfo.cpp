//
// Created by inside on 7/3/16.
//

#include "CommentInfo.h"

namespace Instagram {

CommentInfo::CommentInfo() : BaseResult{} {}

CommentInfo::CommentInfo(const std::string& text, const std::string& id, long createTime, const UserInfo& userInfo) : BaseResult{}, m_text{text}, m_id{id}, m_createTime{createTime}, m_userInfo{userInfo} {}

CommentInfo::CommentInfo(const CommentInfo& commentInfo) : BaseResult{commentInfo}, m_text{commentInfo.m_text}, m_id{commentInfo.m_id}, m_createTime{commentInfo.m_createTime}, m_userInfo{commentInfo.m_userInfo} {}

CommentInfo::CommentInfo(CommentInfo&& commentInfo) : BaseResult{std::move(commentInfo)},
                                                       m_text{std::move(commentInfo.m_text)},
                                                       m_id{std::move(commentInfo.m_id)},
                                                       m_createTime{commentInfo.m_createTime},
                                                       m_userInfo{std::move(commentInfo.m_userInfo) } {
    commentInfo.m_createTime = -1;
}

CommentInfo::CommentInfo(const std::string& errMsg) : BaseResult{errMsg} {}

CommentInfo::CommentInfo(const char* errMsg) : BaseResult{errMsg} {}

CommentInfo::~CommentInfo() {}

CommentInfo& CommentInfo::operator=(const CommentInfo& commentInfo) {
    if (this == &commentInfo) {
        return *this;
    }

    BaseResult::operator=(commentInfo);

    m_text = commentInfo.m_text;
    m_id = commentInfo.m_id;
    m_createTime = commentInfo.m_createTime;
    m_userInfo = commentInfo.m_userInfo;

    return *this;
}

CommentInfo& CommentInfo::operator=(CommentInfo&& commentInfo) {
    if (this == &commentInfo) {
        return *this;
    }

    BaseResult::operator=(std::forward<BaseResult>(commentInfo));
    m_text = std::move(commentInfo.m_text);

    m_id = commentInfo.m_id;
    commentInfo.m_id = -1;

    m_createTime = commentInfo.m_createTime;
    commentInfo.m_createTime = -1;

    m_userInfo = std::move(commentInfo.m_userInfo);
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

}
