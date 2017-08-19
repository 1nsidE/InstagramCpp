#ifndef USERS_INFO_H
#define USERS_INFO_H

#include "UserInfo.h"
#include "ResultCollection.hpp"

namespace Instagram{

using UsersInfo = ResultCollection<UserInfo>;
    
#ifdef WIN32
INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM ResultCollection<UserInfo>;
#endif

}
#endif
