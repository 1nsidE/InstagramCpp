#include "AuthorizationToken.h"

namespace Instagram {

AuthorizationToken::AuthorizationToken() {

}

AuthorizationToken::AuthorizationToken(const char* errMsg) : BaseResult{errMsg} {}

AuthorizationToken::AuthorizationToken(const std::string& errMsg) : BaseResult{errMsg} {}


AuthorizationToken::AuthorizationToken(AuthorizationToken& token) : BaseResult{token},
                                                                    m_token(token.m_token),
                                                                    m_id(token.m_id),
                                                                    m_username(token.m_username),
                                                                    m_bio(token.m_bio),
                                                                    m_fullName(token.m_fullName),
                                                                    m_profilePicUrl(token.m_profilePicUrl),
                                                                    m_website{token.m_website} {}

AuthorizationToken::AuthorizationToken(AuthorizationToken&& token) : BaseResult{std::forward<BaseResult>(token)},
                                                                    m_token(std::move(token.m_token)),
                                                                    m_id(std::move(token.m_id)),
                                                                    m_username(std::move(token.m_username)),
                                                                    m_bio(std::move(token.m_bio)),
                                                                    m_fullName(std::move(token.m_fullName)),
                                                                    m_profilePicUrl(std::move(token.m_profilePicUrl)),
                                                                    m_website{std::move(token.m_website)} {}

AuthorizationToken::~AuthorizationToken() {}

const std::string& AuthorizationToken::token() const noexcept {
    return m_token;
}

const std::string& AuthorizationToken::id() const noexcept {
    return m_id;
}

const std::string& AuthorizationToken::username() const noexcept {
    return m_username;
}

const std::string& AuthorizationToken::bio() const noexcept {
    return m_bio;
}

const std::string& AuthorizationToken::fullName() const noexcept {
    return m_fullName;
}

const std::string& AuthorizationToken::profilePictureUrl() const noexcept {
    return m_profilePicUrl;
}

const std::string& AuthorizationToken::website() const noexcept {
    return m_website;
}


AuthorizationToken& AuthorizationToken::setAuthToken(const std::string &token) {
    m_token = token;
    return *this;
}

AuthorizationToken& AuthorizationToken::setId(const std::string &id) {
    m_id = id;
    return *this;
}

AuthorizationToken& AuthorizationToken::setUsername(const std::string &username) {
    m_username = username;
    return *this;
}

AuthorizationToken& AuthorizationToken::setUserBio(const std::string &bio) {
    m_bio = bio;
    return *this;
}

AuthorizationToken& AuthorizationToken::setFullName(const std::string &fullName) {
    m_fullName = fullName;
    return *this;
}

AuthorizationToken& AuthorizationToken::setProfilePictureUrl(const std::string &profilePicUrl) {
    m_profilePicUrl = profilePicUrl;
    return *this;
}

AuthorizationToken& AuthorizationToken::setWebsite(const std::string &website) {
    m_website = website;
    return *this;
}

}
