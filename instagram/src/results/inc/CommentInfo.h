#ifndef COMMENT_INFO_H
#define COMMENT_INFO_H

#include "BaseResult.h"
#include "UserInfo.h"

namespace Instagram{

class EXPORT_INSTAGRAM CommentInfo : public BaseResult{
public:
    CommentInfo();
    CommentInfo(const std::string& text, const std::string& id, long createTime, const UserInfo& userInfo);
    CommentInfo(const CommentInfo& commentInfo);
    CommentInfo(CommentInfo&& commentInfo);
    CommentInfo(const std::string& errMsg);
    CommentInfo(const char* errMsg);

    ~CommentInfo();

    CommentInfo& operator=(const CommentInfo& commentInfo);
    CommentInfo& operator=(CommentInfo&& commentInfo);

    const std::string& text() const noexcept;
    const std::string& id() const noexcept;
    long createTime() const noexcept;
    const UserInfo& userInfo() const noexcept;

    void setText(const std::string &text);
    void setId(const std::string &id_);
    void setCreateTime(long createdTime);
    void setUserInfo(const UserInfo& userInfo);
    void setUserInfo(UserInfo&& userInfo);
private:
    std::string m_text{""};
    std::string m_id {""};
    long m_createTime = -1;
    UserInfo m_userInfo{};

    friend void swap(CommentInfo& first, CommentInfo& second);
};

}
#endif
