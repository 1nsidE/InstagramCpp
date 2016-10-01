#ifndef AUTHORIZATION_TOKEN
#define AUTHORIZATION_TOKEN

#include "BaseResult.h"

namespace Instagram{

class EXPORT_INSTAGRAM AuthorizationToken : public BaseResult{
public:
    AuthorizationToken();
    AuthorizationToken(const char* err_msg);
    AuthorizationToken(const std::string& err_msg);
    ~AuthorizationToken();

    AuthorizationToken(AuthorizationToken& auth_token);
    AuthorizationToken(AuthorizationToken&& auth_token);

    const std::string& get_auth_token() const noexcept ;
    const std::string& get_id() const noexcept;
    const std::string& get_user_name() const noexcept;
    const std::string& get_user_bio() const noexcept;
    const std::string& get_user_full_name() const noexcept;
    const std::string& get_user_profpic_url() const noexcept;
    const std::string& get_website() const noexcept;

    AuthorizationToken& set_auth_token(const std::string& _auth_token);
    AuthorizationToken& set_id(const std::string& _id);
    AuthorizationToken& set_user_name(const std::string& _user_name);
    AuthorizationToken& set_user_bio(const std::string& _user_bio);
    AuthorizationToken& set_user_full_name(const std::string& _user_full_name);
    AuthorizationToken& set_user_profpic_url(const std::string& _user_profpic_url);
    AuthorizationToken& set_website(const std::string& _website);
private:
    std::string auth_token;
    std::string id;
    std::string user_name;
    std::string user_bio;
    std::string user_full_name;
    std::string profpic_url;
    std::string website;
};

}
#endif
