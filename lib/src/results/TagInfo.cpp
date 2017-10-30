#include "TagInfo.h"

namespace Instagram {

TagInfo::TagInfo() : BaseResult{} {}

TagInfo::TagInfo(const char* errMsg) : BaseResult{errMsg} {}

TagInfo::TagInfo(const std::string& errMsg) : BaseResult{errMsg} {}

TagInfo::TagInfo(const std::string& name, int count) : BaseResult{}, m_name{name}, m_count{count} {}

TagInfo::TagInfo(const TagInfo& tagInfo) : BaseResult{tagInfo}, m_name{tagInfo.m_name}, m_count{tagInfo.m_count} {}

TagInfo::TagInfo(TagInfo&& tagInfo) : TagInfo(){
    swap(*this, tagInfo);
}

TagInfo::~TagInfo() {}

TagInfo& TagInfo::operator=(const TagInfo& tagInfo) {
    TagInfo copy{tagInfo};

    swap(*this, copy);
    return *this;
}

TagInfo& TagInfo::operator=(TagInfo&& tagInfo) {
    swap(*this, tagInfo);

    TagInfo temp{};
    swap(tagInfo, temp);
    return *this;
}

const std::string& TagInfo::name() const noexcept {
    return m_name;
}

int TagInfo::count() const noexcept {
    return m_count;
}

void TagInfo::setName(const std::string& name) {
    m_name = name;
}

void TagInfo::setCount(int count) {
    m_count = count;
}

void swap(TagInfo& first, TagInfo& second){
    using std::swap;
    swap(static_cast<BaseResult&>(first), static_cast<BaseResult&>(second));

    swap(first.m_name, second.m_name);
    swap(first.m_count, second.m_count);
}

}
