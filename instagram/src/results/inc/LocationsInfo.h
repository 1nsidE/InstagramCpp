#ifndef LOCATIONS_INFO_H
#define LOCATIONS_INFO_H

#include "LocationInfo.h"
#include "ResultCollection.hpp"

namespace Instagram{
#ifdef WIN32
INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM std::vector<Instagram::LocationInfo>;
#endif

using LocationsInfo = ResultCollection<LocationInfo>;

}

#endif
