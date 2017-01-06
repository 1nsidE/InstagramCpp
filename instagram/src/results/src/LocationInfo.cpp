#include "LocationInfo.h"

namespace Instagram {

LocationInfo::LocationInfo() : BaseResult{} {}

LocationInfo::LocationInfo(const LocationInfo& locInfo) : BaseResult{locInfo}, m_id{locInfo.m_id}, m_name{locInfo.m_name}, m_lat{locInfo.m_lat}, m_lng{locInfo.m_lng} {}

LocationInfo::LocationInfo(LocationInfo&& locInfo) : LocationInfo(){
    swap(*this, locInfo);
}

LocationInfo::LocationInfo(const std::string& errMsg) : BaseResult{errMsg} {}

LocationInfo::LocationInfo(const char* errMsg) : BaseResult{errMsg} {}

LocationInfo& LocationInfo::operator=(const LocationInfo& locInfo) {
    LocationInfo copy{locInfo};

    swap(*this, copy);
    return *this;
}

LocationInfo& LocationInfo::operator=(LocationInfo&& locInfo) {
    swap(*this, locInfo);

    LocationInfo temp{};
    swap(locInfo, temp);
    return *this;
}

const std::string& LocationInfo::id() const {
    return m_id;
}

const std::string& LocationInfo::name() const {
    return m_name;
}

double LocationInfo::latitude() const {
    return m_lat;
}

double LocationInfo::longitude() const {
    return m_lng;
}

void LocationInfo::setId(const std::string &id) {
    m_id = id;
}

void LocationInfo::setName(const std::string &name) {
    m_name = name;
}

void LocationInfo::setLatitude(double lat) {
    m_lat = lat;
}

void LocationInfo::setLongitude(double lng) {
    m_lng = lng;
}

void swap(LocationInfo& first, LocationInfo& second){
    using std::swap;
    swap(static_cast<BaseResult&>(first), static_cast<BaseResult&>(second));

    swap(first.m_id, second.m_id);
    swap(first.m_name, second.m_name);
    swap(first.m_lat, second.m_lat);
    swap(first.m_lng, second.m_lng);
}

}
