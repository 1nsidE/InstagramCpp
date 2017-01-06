#include "AuthorizationToken.h"

namespace Instagram {

AuthorizationToken::AuthorizationToken() {

}

AuthorizationToken::AuthorizationToken(const char* errMsg) : BaseResult{errMsg} {}

AuthorizationToken::AuthorizationToken(const std::string& errMsg) : BaseResult{errMsg} {}


AuthorizationToken::AuthorizationToken(const AuthorizationToken& token) : BaseResult{token},
                                                                    m_token(token.m_token),
                                                                    m_userInfo{token.m_userInfo}{}

AuthorizationToken::AuthorizationToken(AuthorizationToken&& token) : AuthorizationToken{} {
    swap(*this, token);
}

AuthorizationToken::~AuthorizationToken() {}

const std::string& AuthorizationToken::token() const noexcept {
    return m_token;
}

const UserInfo& AuthorizationToken::userInfo() const noexcept{
    return m_userInfo;
}

void AuthorizationToken::setAuthToken(const std::string& token){
    m_token = token;
}

void AuthorizationToken::setUserInfo(const UserInfo& userInfo){
    m_userInfo = userInfo;
}

void AuthorizationToken::setUserInfo(UserInfo&& userInfo){
    m_userInfo = std::move(userInfo);
}

void swap(AuthorizationToken& first, AuthorizationToken& second){
    using std::swap;
    swap(static_cast<BaseResult&>(first), static_cast<BaseResult&>(second));
    swap(first.m_token, second.m_token);
    swap(first.m_userInfo, second.m_userInfo);
}

}
