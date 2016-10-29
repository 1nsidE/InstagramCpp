#ifndef COMMENTS_INFO_H
#define COMMENTS_INFO_H

#include "ResultCollection.hpp"
#include "CommentInfo.h"

namespace Instagram{

using CommentsInfo = ResultCollection<CommentInfo>;

#ifdef WIN32
INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM ResultCollection<CommentInfo>;
#endif

}
#endif
