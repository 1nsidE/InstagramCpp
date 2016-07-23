#include "LocationsInfo.h"

namespace Instagram{

    LocationsInfo::LocationsInfo() : BaseResult{}, locations(0) {}

    LocationsInfo::LocationsInfo(const LocationsInfo& info) : BaseResult{info}, locations{info.locations} {}

    LocationsInfo::LocationsInfo(LocationsInfo&& info) : BaseResult{std::move(info)}, locations{std::move(info.locations)} {}

    LocationsInfo::LocationsInfo(const std::string& err_msg) : BaseResult{err_msg}, locations(0) {}

    LocationsInfo::LocationsInfo(const char* err_msg) : BaseResult{err_msg}, locations(0) {}

    LocationsInfo& LocationsInfo::operator=(const LocationsInfo& info){
        if(this == &info){
            return *this;
        }

        BaseResult::operator=(info);

        locations = info.locations;
        return *this;
    }

    LocationsInfo& LocationsInfo::operator=(LocationsInfo&& info){
        if(this == &info){
            return *this;
        }

        BaseResult::operator=(std::move(info));

        locations = std::move(info.locations);
        return *this;
    }

    const std::vector<LocationInfo>& LocationsInfo::get_locations() const{
        return locations;
    }

    void LocationsInfo::add_location(const LocationInfo& loc){
        locations.push_back(loc);
    }

    void LocationsInfo::add_location(LocationInfo&& loc){
        locations.push_back(std::move(loc));
    }

    LocationsInfo& LocationsInfo::operator<<(const LocationInfo& loc){
        add_location(loc);
        return *this;
    }

    LocationsInfo& LocationsInfo::operator<<(LocationInfo&& loc){
        add_location(std::move(loc));
        return *this;
    }

}
