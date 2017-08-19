#ifndef LOCATIONS_INFO_H
#define LOCATIONS_INFO_H

#include "LocationInfo.h"
#include "ResultCollection.hpp"

namespace Instagram{

using LocationsInfo = ResultCollection<LocationInfo>;
    
#ifdef WIN32
INSTAGRAM_EXP_TMP template class EXPORT_INSTAGRAM  ResultCollection<LocationInfo>;
#endif

}

#endif
