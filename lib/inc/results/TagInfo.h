#ifndef TAG_INFO_H
#define TAG_INFO_H

#include "BaseResult.h"

namespace Instagram{

class EXPORT_INSTAGRAM TagInfo : public BaseResult{
public:
    TagInfo();
    TagInfo(const std::string& name, int count);
    TagInfo(const char* errMsg);
    TagInfo(const std::string& errMsg);
    TagInfo(const TagInfo& tagInfo);
    TagInfo(TagInfo&& tagInfo);

    ~TagInfo();

    TagInfo& operator=(const TagInfo& tagInfo);
    TagInfo& operator=(TagInfo&& tagInfo);

    const std::string& name() const noexcept;
    int count() const noexcept;

    void setName(const std::string& name);
    void setCount(int count);
private:
    std::string m_name{};
    int m_count{-1};

    friend void swap(TagInfo& first, TagInfo& second);
};

}

#endif

