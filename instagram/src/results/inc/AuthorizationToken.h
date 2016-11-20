#ifndef AUTHORIZATION_TOKEN
#define AUTHORIZATION_TOKEN

#include "BaseResult.h"

namespace Instagram{

class EXPORT_INSTAGRAM AuthorizationToken : public BaseResult{
public:
    AuthorizationToken();
    AuthorizationToken(const char* errMsg);
    AuthorizationToken(const std::string& errMsg);
    ~AuthorizationToken();

    AuthorizationToken(AuthorizationToken& authToken);
    AuthorizationToken(AuthorizationToken&& authToken);

    const std::string& token() const noexcept ;
    const std::string& id() const noexcept;
    const std::string& username() const noexcept;
    const std::string& bio() const noexcept;
    const std::string& fullName() const noexcept;
    const std::string& profilePictureUrl() const noexcept;
    const std::string& website() const noexcept;

    AuthorizationToken& setAuthToken(const std::string &authToken);
    AuthorizationToken& setId(const std::string &id);
    AuthorizationToken& setUsername(const std::string &username);
    AuthorizationToken& setUserBio(const std::string &userBio);
    AuthorizationToken& setFullName(const std::string &userFullName);
    AuthorizationToken& setProfilePictureUrl(const std::string &userProfilePictureUrl);
    AuthorizationToken& setWebsite(const std::string &website);
private:
    std::string m_token;
    std::string m_id;
    std::string m_username;
    std::string m_bio;
    std::string m_fullName;
    std::string m_profilePicUrl;
    std::string m_website;
};

}
#endif
