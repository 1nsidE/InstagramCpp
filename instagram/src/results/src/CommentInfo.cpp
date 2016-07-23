//
// Created by inside on 7/3/16.
//

#include "CommentInfo.h"

namespace Instagram{

    CommentInfo::CommentInfo() : BaseResult{} {}

    CommentInfo::CommentInfo(const std::string& text_, const std::string& id_, long created_time_, const UserInfo& user_info_) : BaseResult{}, text{text_}, id{id_}, created_time{created_time_}, user_info{user_info_} {}

    CommentInfo::CommentInfo(const CommentInfo& comment_info) : BaseResult{comment_info}, text{comment_info.text}, id{comment_info.id}, created_time{comment_info.created_time}, user_info{comment_info.user_info} {}

    CommentInfo::CommentInfo(CommentInfo&& comment_info) : BaseResult{std::forward<BaseResult>(comment_info)},
                                                           text{std::move(comment_info.text)},
                                                           id{comment_info.id},
                                                           created_time{comment_info.created_time},
                                                           user_info{std::move(comment_info.user_info)}{
        comment_info.id = -1;
        comment_info.created_time = -1;
    }

    CommentInfo::CommentInfo(const std::string& err_msg) : BaseResult{err_msg} {}

    CommentInfo::CommentInfo(const char* err_msg) : BaseResult{err_msg} { }

    CommentInfo::~CommentInfo(){}

    CommentInfo& CommentInfo::operator=(const CommentInfo& comment_info){
        if(this == &comment_info){
            return *this;
        }

        BaseResult::operator=(comment_info);

        text = comment_info.text;
        id = comment_info.id;
        created_time = comment_info.created_time;
        user_info = comment_info.user_info;

        return *this;
    }

    CommentInfo& CommentInfo::operator=(CommentInfo&& comment_info){
        if(this == &comment_info){
            return *this;
        }

        BaseResult::operator=(std::forward<BaseResult>(comment_info));
        text = std::move(comment_info.text);

        id = comment_info.id;
        comment_info.id = -1;

        created_time = comment_info.created_time;
        comment_info.created_time = -1;

        user_info = std::move(comment_info.user_info);
        return *this;
    }

    const std::string& CommentInfo::get_text() const noexcept{
        return text;
    }

    const std::string& CommentInfo::get_id() const noexcept{
        return id;
    }

    long CommentInfo::get_created_time() const noexcept{
        return created_time;
    }

    const UserInfo& CommentInfo::get_user_info() const noexcept{
        return user_info;
    }

    void CommentInfo::set_text(const std::string& text_){
        text = text_;
    }

    void CommentInfo::set_id(const std::string&  id_){
        id = id_;
    }

    void CommentInfo::set_created_time(long create_time_){
        created_time = create_time_;
    }

    void CommentInfo::set_user_info(const UserInfo& user_info_){
        user_info = user_info_;
    }

}
