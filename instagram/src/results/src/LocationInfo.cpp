#include "LocationInfo.h"

namespace Instagram {

LocationInfo::LocationInfo() : BaseResult{} {}

LocationInfo::LocationInfo(const LocationInfo& locInfo) : BaseResult{locInfo}, m_id{locInfo.m_id}, m_name{locInfo.m_name}, m_lat{locInfo.m_lat}, m_lng{locInfo.m_lng} {}

LocationInfo::LocationInfo(LocationInfo&& locInfo) : BaseResult{std::move(locInfo)}, m_id{std::move(locInfo.m_id)}, m_name{std::move(locInfo.m_name)}, m_lat{locInfo.m_lat}, m_lng{locInfo.m_lng} {
    locInfo.m_lat = -1;
    locInfo.m_lng = -1;
}

LocationInfo::LocationInfo(const std::string& errMsg) : BaseResult{errMsg} {}

LocationInfo::LocationInfo(const char* errMsg) : BaseResult{errMsg} {}

LocationInfo& LocationInfo::operator=(const LocationInfo& locInfo) {
    if (this == &locInfo) {
        return *this;
    }

    BaseResult::operator=(locInfo);

    m_id = locInfo.m_id;
    m_name = locInfo.m_name;
    m_lat = locInfo.m_lat;
    m_lng = locInfo.m_lng;

    return *this;
}

LocationInfo& LocationInfo::operator=(LocationInfo&& locInfo) {
    if (this == &locInfo) {
        return *this;
    }

    BaseResult::operator=(std::move(locInfo));
    m_id = std::move(locInfo.m_id);
    m_name = std::move(locInfo.m_name);

    m_lat = locInfo.m_lat;
    locInfo.m_lat = -1;

    m_lng = locInfo.m_lng;
    locInfo.m_lng = -1;

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

}
