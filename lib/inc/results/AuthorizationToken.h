#ifndef AUTHORIZATION_TOKEN
#define AUTHORIZATION_TOKEN

#include "UserInfo.h"

namespace Instagram{

class EXPORT_INSTAGRAM AuthorizationToken : public BaseResult{
public:
    AuthorizationToken();
    AuthorizationToken(const char* errMsg);
    AuthorizationToken(const std::string& errMsg);
    ~AuthorizationToken();

    AuthorizationToken(const AuthorizationToken& authToken);
    AuthorizationToken(AuthorizationToken&& authToken);

    const std::string& token() const noexcept;
    const UserInfo& userInfo() const noexcept;

    void setAuthToken(const std::string& token);
    void setUserInfo(const UserInfo& userInfo);
    void setUserInfo(UserInfo&& userInfo);
private:
    std::string m_token {};
    UserInfo m_userInfo{};

    friend void swap(AuthorizationToken& first, AuthorizationToken& second);
};

}
#endif
