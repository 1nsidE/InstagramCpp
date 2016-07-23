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

        const std::string& get_id() const noexcept;
        const std::string& get_username() const noexcept;
        const std::string& get_name() const noexcept;
        const std::string& get_last_name() const noexcept;
        const std::string& get_bio() const noexcept;
        const std::string& get_prof_pic_url() const noexcept;
        const std::string& get_website() const noexcept;

        int followed_by() const noexcept;
        int follows() const noexcept;
        int media_count() const noexcept;

        void set_id(const std::string& _id);
        void set_username(const std::string& _username);
        void set_name(const std::string& _name);
        void set_last_name(const std::string& _last_name);
        void set_bio(const std::string& _bio);
        void set_prof_pic_url(const std::string& _prof_pic_url);
        void set_website(const std::string& _website);

        void set_followed_by(int count);
        void set_follows(int count);
        void set_media_count(int count);
    private:
        std::string id;
        std::string username;
        std::string name;
        std::string last_name;
        std::string bio;
        std::string prof_pic_url;
        std::string website;

        int _followed_by;
        int _follows;
        int _media_count;
    };

}

#endif
