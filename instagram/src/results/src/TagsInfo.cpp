#include"TagsInfo.h"

namespace Instagram {

TagsInfo::TagsInfo() : BaseResult{}, tags(0) {}

TagsInfo::TagsInfo(const char* err_msg) : BaseResult{ err_msg }, tags(0) {}

TagsInfo::TagsInfo(const std::string& err_msg) : BaseResult{ err_msg }, tags(0) {}

TagsInfo::TagsInfo(const TagsInfo& tags_info) : BaseResult{ tags_info }, tags{ tags_info.tags } {}

TagsInfo::TagsInfo(TagsInfo&& tags_info) : BaseResult{ std::forward<BaseResult>(tags_info) }, tags{ std::move(tags_info.tags) } {}

TagsInfo::~TagsInfo() {}

TagsInfo& TagsInfo::operator=(const TagsInfo& tags_info) {
    if (this == &tags_info) {
        return *this;
    }

    BaseResult::operator=(tags_info);

    tags = tags_info.tags;

    return *this;
}

TagsInfo& TagsInfo::operator=(TagsInfo&& tags_info) {
    if (this == &tags_info) {
        return *this;
    }

    BaseResult::operator=(std::forward<BaseResult>(tags_info));

    tags = std::move(tags_info.tags);

    return *this;
}

void TagsInfo::add_tag(const TagInfo& tag_info) {
    tags.push_back(tag_info);
}

void TagsInfo::add_tag(TagInfo&& tag_info) {
    tags.push_back(std::forward<TagInfo>(tag_info));
}

const TagsInfo& TagsInfo::operator<<(const TagInfo& tag_info) {
    add_tag(tag_info);
    return *this;
}

const TagsInfo& TagsInfo::operator<<(TagInfo&& tag_info) {
    add_tag(std::forward<TagInfo>(tag_info));
    return *this;
}

const std::vector<TagInfo>& TagsInfo::get_tags() const noexcept {
    return tags;
}

TagInfo& TagsInfo::operator[](size_t n) {
    return tags[n];
}

const TagInfo& TagsInfo::operator[](size_t n) const {
    return tags[n];
}

TagsInfo::iterator TagsInfo::begin() {
    return tags.begin();
}

TagsInfo::iterator TagsInfo::end() {
    return tags.end();
}

TagsInfo::const_iterator TagsInfo::begin() const {
    return tags.begin();
}

TagsInfo::const_iterator TagsInfo::end() const {
    return tags.end();
}

void TagsInfo::clear() {
    tags.clear();
}

}
