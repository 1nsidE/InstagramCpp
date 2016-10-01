#include "AuthorizationToken.h"

namespace Instagram {

AuthorizationToken::AuthorizationToken() {

}

AuthorizationToken::AuthorizationToken(const char* err_msg) : BaseResult(err_msg) {}

AuthorizationToken::AuthorizationToken(const std::string& err_msg) : BaseResult{ err_msg } {}


AuthorizationToken::AuthorizationToken(AuthorizationToken& token) : BaseResult{ token },
                                                                    auth_token(token.auth_token),
                                                                    id(token.id),
                                                                    user_name(token.user_name),
                                                                    user_bio(token.user_bio),
                                                                    user_full_name(token.user_full_name),
                                                                    profpic_url(token.profpic_url){}

AuthorizationToken::AuthorizationToken(AuthorizationToken&& token) : BaseResult{ std::forward<BaseResult>(token) },
                                                                     auth_token(std::move(token.auth_token)),
                                                                     id(std::move(token.id)),
                                                                     user_name(std::move(token.user_name)),
                                                                     user_bio(std::move(token.user_bio)),
                                                                     user_full_name(std::move(token.user_full_name)),
                                                                     profpic_url(std::move(token.profpic_url)){}

AuthorizationToken::~AuthorizationToken() {

}

const std::string& AuthorizationToken::get_auth_token() const noexcept {
    return auth_token;
}

const std::string& AuthorizationToken::get_id() const noexcept {
    return id;
}

const std::string& AuthorizationToken::get_user_name() const noexcept {
    return user_name;
}

const std::string& AuthorizationToken::get_user_bio() const noexcept {
    return user_bio;
}

const std::string& AuthorizationToken::get_user_full_name() const noexcept {
    return user_full_name;
}

const std::string& AuthorizationToken::get_user_profpic_url() const noexcept {
    return profpic_url;
}

const std::string& AuthorizationToken::get_website() const noexcept {
    return website;
}


AuthorizationToken& AuthorizationToken::set_auth_token(const std::string& _auth_token) {
    auth_token = _auth_token;
    return *this;
}

AuthorizationToken& AuthorizationToken::set_id(const std::string& _id) {
    id = _id;
    return *this;
}

AuthorizationToken& AuthorizationToken::set_user_name(const std::string& _user_name) {
    user_name = _user_name;
    return *this;
}

AuthorizationToken& AuthorizationToken::set_user_bio(const std::string& _user_bio) {
    user_bio = _user_bio;
    return *this;
}

AuthorizationToken& AuthorizationToken::set_user_full_name(const std::string& _user_full_name) {
    user_full_name = _user_full_name;
    return *this;
}

AuthorizationToken& AuthorizationToken::set_user_profpic_url(const std::string& _profpic_url) {
    profpic_url = _profpic_url;
    return *this;
}

AuthorizationToken& AuthorizationToken::set_website(const std::string& _website) {
    website = _website;
    return *this;
}

}
