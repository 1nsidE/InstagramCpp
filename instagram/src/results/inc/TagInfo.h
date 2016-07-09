#ifndef TAG_INFO_H
#define TAG_INFO_H

#include "BaseResult.h"

namespace Instagram{

class TagInfo : public BaseResult{
public:
    TagInfo();
    TagInfo(const std::string& name_, int count_);
    TagInfo(const char* err_msg);
    TagInfo(const std::string& err_msg);
    TagInfo(const TagInfo& tag_info);
    TagInfo(TagInfo&& tag_info);

    ~TagInfo();    
    
    const TagInfo& operator=(const TagInfo& tag_info);
    const TagInfo& operator=(TagInfo&& tag_info);

    const std::string& get_name() const noexcept;
    int get_count() const noexcept;

    void set_name(const std::string& name_);
    void set_count(int count_);
private:
    std::string name{""};
    int count = -1;
};

}

#endif

