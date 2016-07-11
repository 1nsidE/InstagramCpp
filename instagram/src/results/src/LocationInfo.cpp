#include "LocationInfo.h"

namespace Instagram{

LocationInfo::LocationInfo() : BaseResult{} {}

LocationInfo::LocationInfo(const LocationInfo& loc_info) : BaseResult{loc_info}, id{loc_info.id}, name{loc_info.name}, lat{loc_info.lat}, lng{loc_info.lng} {}

LocationInfo::LocationInfo(LocationInfo&& loc_info) : BaseResult{std::move(loc_info)}, id{std::move(loc_info.id)}, name{std::move(loc_info.name)}, lat{loc_info.lat}, lng{loc_info.lng} {
    loc_info.lat = -1;
    loc_info.lng = -1;
}

LocationInfo::LocationInfo(const std::string& err_msg) : BaseResult{err_msg} {}

LocationInfo::LocationInfo(const char* err_msg) : BaseResult{err_msg} {}

LocationInfo& LocationInfo::operator=(const LocationInfo& loc_info){
    if(this == &loc_info){
        return *this;
    }

    BaseResult::operator=(loc_info);

    id = loc_info.id;
    name = loc_info.name;
    lat = loc_info.lat;
    lng = loc_info.lng;

    return *this;
}

LocationInfo& LocationInfo::operator=(LocationInfo&& loc_info){
    if(this == & loc_info){
        return *this;
    }

    BaseResult::operator=(std::move(loc_info));
    id = std::move(loc_info.id);
    name = std::move(loc_info.name);
    
    lat = loc_info.lat;
    loc_info.lat = -1;

    lng = loc_info.lng;
    loc_info.lng = -1;

    return *this;
}

const std::string& LocationInfo::get_id() const{
    return id;
}

const std::string& LocationInfo::get_name() const{
    return name;
}

double LocationInfo::get_latitude() const{
    return lat;
}

double LocationInfo::get_longitude() const{
    return lng;
}

void LocationInfo::set_id(const std::string& id_){
    id = id_;
}

void LocationInfo::set_name(const std::string& name_){
    name = name_;
}

void LocationInfo::set_latitude(double lat_){
    lat = lat_;
}

void LocationInfo::set_longitude(double lng_){
    lng = lng_;
}

}
