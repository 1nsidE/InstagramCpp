#ifndef LOCATIONS_INFO_H
#define LOCATIONS_INFO_H

#include "BaseResult.h"
#include "LocationInfo.h"
#include <vector>

namespace Instagram{

class LocationsInfo : public  BaseResult{
public:
    LocationsInfo();
    LocationsInfo(const LocationsInfo& loc_info);
    LocationsInfo(LocationsInfo&& loc_info);
    LocationsInfo(const std::string& err_msg);
    LocationsInfo(const char* er_msg);

    LocationsInfo& operator=(const LocationsInfo& loc_info);
    LocationsInfo& operator=(LocationsInfo&& loc_info);

    const std::vector<LocationInfo>& get_locations() const;
    
    void add_location(const LocationInfo& loc_info);
    void add_location(LocationInfo&& loc_info);
    LocationsInfo& operator<<(const LocationInfo& loc_info);
    LocationsInfo& operator<<(LocationInfo&& loc_info);
private:
    std::vector<LocationInfo> locations;
};

}

#endif
