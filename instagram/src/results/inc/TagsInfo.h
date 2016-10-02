#ifndef TAGS_INFO_H
#define TAGS_INFO_H

#include <vector>
#include "TagInfo.h"
#include "ResultCollection.hpp"

namespace Instagram{
#ifdef WIN32
INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM std::vector<Instagram::TagInfo>;
#endif

using TagsInfo = ResultCollection<TagInfo>;

}
#endif
