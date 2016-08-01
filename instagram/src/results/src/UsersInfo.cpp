#include "UsersInfo.h"

namespace Instagram {

    UsersInfo::UsersInfo() : BaseResult{}, users(0) {}

    UsersInfo::UsersInfo(const UsersInfo& info) : BaseResult{ info }, users{ info.users } {}

    UsersInfo::UsersInfo(UsersInfo&& info) : BaseResult{ std::forward<BaseResult>(info) }, users{ std::move(info.users) } {}

    UsersInfo::UsersInfo(const char* err_msg) : BaseResult{ err_msg }, users(0) {}

    UsersInfo::UsersInfo(const std::string& err_msg) : BaseResult{ err_msg }, users(0) {}

    UsersInfo::~UsersInfo() {}

    UsersInfo& UsersInfo::operator=(const UsersInfo& info) {
        if (this == &info) {
            return *this;
        }

        BaseResult::operator=(info);
        users = info.users;

        return *this;
    }

    UsersInfo& UsersInfo::operator=(UsersInfo&& info) {
        if (this == &info) {
            return *this;
        }

        BaseResult::operator=(std::forward<BaseResult>(info));
        users = std::move(info.users);

        return *this;
    }

    UsersInfo& UsersInfo::operator<<(const UserInfo& info) {
        add_info(info);
        return *this;
    }

    UsersInfo& UsersInfo::operator<<(UserInfo&& info) {
        add_info(std::forward<UserInfo>(info));
        return *this;
    }

    void UsersInfo::add_info(const UserInfo& info) {
        users.push_back(info);
    }

    void UsersInfo::add_info(UserInfo&& info) {
        users.push_back(std::forward<UserInfo>(info));
    }

    const std::vector<UserInfo>& UsersInfo::get_users() const noexcept {
        return users;
    }

    UserInfo& UsersInfo::operator[](size_t n) {
        return users[n];
    }

    const UserInfo& UsersInfo::operator[](size_t n) const {
        return users[n];
    }

    UsersInfo::iterator UsersInfo::begin() {
        return users.begin();
    }

    UsersInfo::iterator UsersInfo::end() {
        return users.end();
    }

    UsersInfo::const_iterator UsersInfo::begin() const {
        return users.begin();
    }

    UsersInfo::const_iterator UsersInfo::end() const {
        return users.end();
    }
}
