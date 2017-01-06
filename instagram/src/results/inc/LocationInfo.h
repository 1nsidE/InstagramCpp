#ifndef LOCATION_INFO_H
#define LOCATION_INFO_H

#include "BaseResult.h"

namespace Instagram{

class EXPORT_INSTAGRAM LocationInfo : public BaseResult{
public:
    LocationInfo();
    LocationInfo(const LocationInfo& locInfo);
    LocationInfo(LocationInfo&& locInfo);
    LocationInfo(const std::string& errMsg);
    LocationInfo(const char* errMsg);

    LocationInfo& operator=(const LocationInfo& locInfo);
    LocationInfo& operator=(LocationInfo&& locInfo);

    const std::string& id() const;
    const std::string& name() const;
    double latitude() const;
    double longitude() const;

    void setId(const std::string &id);
    void setName(const std::string &name);
    void setLatitude(double lat);
    void setLongitude(double lng);
private:
    std::string m_id{""};
    std::string m_name{""};
    double m_lat{-1};
    double m_lng{-1};

    friend void swap(LocationInfo& first, LocationInfo& second);
};

}


#endif
