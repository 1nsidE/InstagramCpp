#ifndef TAGS_INFO_H
#define TAGS_INFO_H

#include <vector>
#include "TagInfo.h"
#include"BaseResult.h"

namespace Instagram{

class TagsInfo : public BaseResult{
public:
    TagsInfo();
    TagsInfo(const char* err_msg);
    TagsInfo(const std::string& err_msg);
    TagsInfo(const TagsInfo& tags_info);
    TagsInfo(TagsInfo&& tags_info);
    ~TagsInfo();
    
    TagsInfo& operator=(const TagsInfo& tags_info);
    TagsInfo& operator=(TagsInfo&& tags_info);

    const std::vector<TagInfo>& get_tags() const noexcept;
    
    void add_tag(const TagInfo& tag_info);
    void add_tag(TagInfo&& tag_info);

    const TagsInfo& operator<<(const TagInfo& tag_info);
    const TagsInfo& operator<<(TagInfo&& tag_info);

    void clear();
private:
    std::vector<TagInfo> tags;
};


}
#endif
