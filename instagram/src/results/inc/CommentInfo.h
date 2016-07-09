#ifndef COMMENT_INFO_H
#define COMMENT_INFO_H

#include "BaseResult.h"
#include "UserInfo.h"

namespace Instagram{

class CommentInfo : public BaseResult{
public:
    CommentInfo();
    CommentInfo(const std::string& text_, const std::string& id_, long created_time_, const UserInfo& user_info_);
    CommentInfo(const CommentInfo& comment_info);
    CommentInfo(CommentInfo&& comment_info);
    CommentInfo(const std::string& err_msg);
    CommentInfo(const char* err_msg);
    
    ~CommentInfo();

    CommentInfo& operator=(const CommentInfo& comment_info);
    CommentInfo& operator=(CommentInfo&& comment_info);
    
    const std::string& get_text() const noexcept;
    const std::string& get_id() const noexcept;
    long get_created_time() const noexcept;
    const UserInfo& get_user_info() const noexcept;

    void set_text(const std::string& text_);
    void set_id(const std::string& id_);
    void set_created_time(long created_time_);
    void set_user_info(const UserInfo& user_info_);
private:
    std::string text{""};
    std::string id {""};
    long created_time = -1;
    UserInfo user_info{};
};

}
#endif
