#ifndef TAGS_INFO_H
#define TAGS_INFO_H

#include <vector>
#include "TagInfo.h"
#include "ResultCollection.hpp"

namespace Instagram{

using TagsInfo = ResultCollection<TagInfo>;
    
#ifdef WIN32
INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM ResultCollection<TagInfo>;
#endif

}
#endif
