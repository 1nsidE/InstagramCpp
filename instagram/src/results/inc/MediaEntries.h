#ifndef MEDIA_ENTRIES_H
#define MEDIA_ENTRIES_H

#include "ResultCollection.hpp"
#include "MediaEntry.h"

namespace Instagram{
    #ifdef WIN32
    INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM std::vector<Instagram::MediaEntry>;
    #endif

using MediaEntries = ResultCollection<MediaEntry>;

}

#endif
