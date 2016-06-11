#include "UsersInfo.h"

namespace Instagram{

UsersInfo::UsersInfo() : BaseResult{}, users(0) {}

UsersInfo::UsersInfo(const UsersInfo& info) : BaseResult{info}, users{info.users} {}

UsersInfo::UsersInfo(UsersInfo&& info) : BaseResult{std::forward<BaseResult>(info)}, users{std::move(info.users)} {}

UsersInfo::UsersInfo(const char* err_msg) : BaseResult{err_msg}, users(0) {}

UsersInfo::UsersInfo(const std::string& err_msg) : BaseResult{err_msg}, users(0) {}

UsersInfo::~UsersInfo() {}

UsersInfo& UsersInfo::operator=(const UsersInfo& info){
    if(this == &info){
        return *this;
    }
    
    BaseResult::operator=(info);
    users = info.users;

    return *this;
}

UsersInfo& UsersInfo::operator=(UsersInfo&& info){
    if(this == &info){
        return *this;
    }

    BaseResult::operator=(std::forward<BaseResult>(info));
    users = std::move(info.users);

    return *this;
}

UsersInfo& UsersInfo::operator<<(const UserInfo& info){
    users.push_back(info);
    return *this;
}

void UsersInfo::add_info(const UserInfo& info){
    users.push_back(info);
}

const std::vector<UserInfo>& UsersInfo::get_users() const{
    return users;
}

}
