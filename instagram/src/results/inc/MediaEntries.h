#ifndef MEDIA_ENTRIES_H
#define MEDIA_ENTRIES_H

#include "ResultCollection.hpp"
#include "MediaEntry.h"

namespace Instagram{

using MediaEntries = ResultCollection<MediaEntry>;
    
#ifdef WIN32
INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM ResultCollection<MediaEntry>;
#endif

}

#endif
