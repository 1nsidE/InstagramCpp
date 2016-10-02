#ifndef USERS_INFO_H
#define USERS_INFO_H

#include "UserInfo.h"
#include "ResultCollection.hpp"

namespace Instagram{
#ifdef WIN32
INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM std::vector<Instagram::UserInfo>;
#endif

using UsersInfo = ResultCollection<UserInfo>;

}
#endif
