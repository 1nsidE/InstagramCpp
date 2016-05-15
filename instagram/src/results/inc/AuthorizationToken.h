#ifndef AUTHORIZATION_TOKEN
#define AUTHORIZATION_TOKEN

#include <string>
#include "BaseResult.h"

namespace Instagram{

class AuthorizationToken : public BaseResult{
public:
    AuthorizationToken();
	AuthorizationToken(const char* err_msg) : BaseResult(err_msg){};
    ~AuthorizationToken();

    AuthorizationToken(AuthorizationToken& auth_token);
    AuthorizationToken(AuthorizationToken&& auth_token);
    
    std::string get_auth_token() const;
	std::string get_id() const;
    std::string get_user_name() const;
    std::string get_user_bio() const;
    std::string get_user_full_name() const;
    std::string get_user_profpic_url() const;
    std::string get_website() const;

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
