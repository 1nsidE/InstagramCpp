#include "UserInfo.h"

namespace Instagram{

UserInfo::UserInfo() : BaseResult() {}

UserInfo::UserInfo(const UserInfo& user_info) : BaseResult{user_info},
                                        id{user_info.id},
                                        nickname{user_info.nickname},
                                        full_name{user_info.full_name},
                                        bio{user_info.bio},
                                        prof_pic_url{user_info.prof_pic_url},
                                        website{user_info.website},
                                        _followed_by{user_info._followed_by},
                                        _follows{user_info._follows},
                                        _media_count{user_info._media_count}{}

UserInfo::UserInfo(UserInfo&& user_info) : BaseResult{user_info},
                                        id{std::move(user_info.id)},
                                        nickname{std::move(user_info.nickname)},
                                        full_name{std::move(user_info.full_name)},
                                        bio{std::move(user_info.bio)},
                                        prof_pic_url{std::move(user_info.prof_pic_url)},
                                        website{std::move(user_info.website)},
                                        _followed_by{user_info._followed_by},
                                        _follows{user_info._follows},
                                        _media_count{user_info._media_count}{

    user_info._follows = 0;
    user_info._followed_by = 0;
    user_info._media_count = 0;
}


UserInfo::UserInfo(const char* err_msg) : BaseResult{err_msg}{}

UserInfo::UserInfo(const std::string& err_msg) : BaseResult{err_msg}{}

UserInfo::~UserInfo(){}

UserInfo& UserInfo::operator=(const UserInfo& user_info){
    if(this == &user_info){
        return *this;
    }

    id = user_info.id;
    nickname = user_info.nickname;
    full_name = user_info.full_name;
    bio = user_info.bio;
    prof_pic_url = user_info.prof_pic_url;
    website = user_info.website;

    _followed_by = user_info._followed_by;
    _follows = user_info._follows;
    _media_count = user_info._media_count;

    return *this;
}

UserInfo& UserInfo::operator=(UserInfo&& user_info){
    if(this == &user_info){
        return *this;
    }
    
    id = std::move(user_info.id);
    nickname = std::move(user_info.nickname);
    full_name = std::move(user_info.full_name);
    bio = std::move(user_info.bio);
    prof_pic_url = std::move(user_info.prof_pic_url);
    website = std::move(user_info.website);

    _followed_by = user_info._followed_by;
    user_info._followed_by = 0;
    _follows = user_info._follows;
    user_info._follows = 0;
    _media_count = user_info._media_count;
    user_info._media_count = 0;
    
    return *this;
}

const std::string& UserInfo::get_id() const{
    return id;
}

const std::string& UserInfo::get_nickname() const{
    return nickname;
}

const std::string& UserInfo::get_full_name() const{
    return full_name;
}

const std::string& UserInfo::get_bio() const{
    return bio;
}

const std::string& UserInfo::get_prof_pic_url() const{
    return prof_pic_url;
}

const std::string& UserInfo::get_website() const{
    return website;
}

unsigned int UserInfo::followed_by() const{
    return _followed_by;
}

unsigned int UserInfo::follows() const{
    return _follows;
}

unsigned int UserInfo::media_count() const{
    return _media_count;
}

void UserInfo::set_id(const std::string& _id){
    id = _id;
}

void UserInfo::set_nickname(const std::string& _nickname){
    nickname = _nickname;
}

void UserInfo::set_full_name(const std::string& _full_name){
    full_name = _full_name;
}

void UserInfo::set_bio(const std::string& _bio){
    bio = _bio;
}

void UserInfo::set_prof_pic_url(const std::string& _prof_pic_url){
    prof_pic_url = _prof_pic_url;
}

void UserInfo::set_website(const std::string& _website){
    website = _website;
}

void UserInfo::set_followed_by(unsigned int count){
    _followed_by = count;
}

void UserInfo::set_follows(unsigned int count){
    _follows = count;
}

void UserInfo::set_media_count(unsigned int count){
    _media_count = count;
}

}
