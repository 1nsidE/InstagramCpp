#ifndef USER_INFO_H
#define USER_INFO_H

#include "BaseResult.h"

namespace Instagram{

class UserInfo : public BaseResult{
public:
    UserInfo();
    UserInfo(const UserInfo& user_info);
    UserInfo(UserInfo&& user_info);

    UserInfo(const char* err_msg);
    UserInfo(const std::string& err_msg);

    ~UserInfo();

    UserInfo& operator=(const UserInfo& user_info);
    UserInfo& operator=(UserInfo&& user_info);
    
    const std::string& get_id() const;
    const std::string& get_nickname() const;
    const std::string& get_full_name() const;
    const std::string& get_bio() const;
    const std::string& get_prof_pic_url() const;
    const std::string& get_website() const;

    unsigned int followed_by() const;
    unsigned int follows() const;
    unsigned int media_count() const;
    
    void set_id(const std::string& _id);
    void set_nickname(const std::string& _nickname);
    void set_full_name(const std::string& _full_name);
    void set_bio(const std::string& _bio);
    void set_prof_pic_url(const std::string& _prof_pic_url);
    void set_website(const std::string& _website);

    void set_followed_by(unsigned int count);
    void set_follows(unsigned int count);
    void set_media_count(unsigned int count);
private:
    std::string id;
    std::string nickname;
    std::string full_name;
    std::string bio;
    std::string prof_pic_url;
    std::string website;

    unsigned int _followed_by;
    unsigned int _follows;
    unsigned int _media_count;
};

}

#endif
