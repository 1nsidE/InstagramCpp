#ifndef LOCATION_INFO_H
#define LOCATION_INFO_H

#include "BaseResult.h"

namespace Instagram{

class LocationInfo : public BaseResult{
public:    
    LocationInfo();
    LocationInfo(const LocationInfo& loc_info);
    LocationInfo(LocationInfo&& loc_info);
    LocationInfo(const std::string& err_msg);
    LocationInfo(const char* err_msg);

    LocationInfo& operator=(const LocationInfo& loc_info);
    LocationInfo& operator=(LocationInfo&& loc_info);

    const std::string& get_id() const;
    const std::string& get_name() const;
    double get_latitude() const;
    double get_longitude() const;

    void set_id(const std::string& id_);
    void set_name(const std::string& name_);
    void set_latitude(double lat_);
    void set_longitude(double lng_);
private:
    std::string id{""};
    std::string name{""};
    double lat{-1};
    double lng{-1};
};

}


#endif
