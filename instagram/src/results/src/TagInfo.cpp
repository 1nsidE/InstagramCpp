#include"TagInfo.h"

namespace Instagram {

TagInfo::TagInfo() : BaseResult{} {}

TagInfo::TagInfo(const char* err_msg) : BaseResult{ err_msg } {}

TagInfo::TagInfo(const std::string& err_msg) : BaseResult{ err_msg } {}

TagInfo::TagInfo(const std::string& name_, int count_) : BaseResult{}, name{ name_ }, count{ count_ } {}

TagInfo::TagInfo(const TagInfo& tag_info) : BaseResult{ tag_info }, name{ tag_info.name }, count{ tag_info.count } {}

TagInfo::TagInfo(TagInfo&& tag_info) : BaseResult{ std::forward<BaseResult>(tag_info) }, name{ std::move(tag_info.name) }, count{ tag_info.count } {
    tag_info.count = -1;
}

TagInfo::~TagInfo() {}

TagInfo& TagInfo::operator=(const TagInfo& tag_info) {
    if (this == &tag_info) {
        return *this;
    }

    BaseResult::operator=(tag_info);

    name = tag_info.name;
    count = tag_info.count;

    return *this;
}

TagInfo& TagInfo::operator=(TagInfo&& tag_info) {
    if (this == &tag_info) {
        return *this;
    }

    BaseResult::operator=(std::forward<BaseResult>(tag_info));

    name = std::move(tag_info.name);
    count = tag_info.count;
    tag_info.count = -1;

    return *this;
}

const std::string& TagInfo::get_name() const noexcept {
    return name;
}

int TagInfo::get_count() const noexcept {
    return count;
}

void TagInfo::set_name(const std::string& name_) {
    name = name_;
}

void TagInfo::set_count(int count_) {
    count = count_;
}

}
