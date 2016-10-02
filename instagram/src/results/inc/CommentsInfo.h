#ifndef COMMENTS_INFO_H
#define COMMENTS_INFO_H

#include "ResultCollection.hpp"
#include "CommentInfo.h"

namespace Instagram{
#ifdef WIN32
INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM std::vector<Instagram::CommentInfo>;
#endif

using CommentsInfo = ResultCollection<CommentInfo>;

}
#endif
