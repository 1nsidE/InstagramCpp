#include"TagInfo.h"

namespace Instagram {

TagInfo::TagInfo() : BaseResult{} {}

TagInfo::TagInfo(const char* errMsg) : BaseResult{errMsg} {}

TagInfo::TagInfo(const std::string& errMsg) : BaseResult{errMsg} {}

TagInfo::TagInfo(const std::string& name, int count) : BaseResult{}, m_name{name}, m_count{count} {}

TagInfo::TagInfo(const TagInfo& tagInfo) : BaseResult{tagInfo}, m_name{tagInfo.m_name}, m_count{tagInfo.m_count} {}

TagInfo::TagInfo(TagInfo&& tagInfo) : BaseResult{std::forward<BaseResult>(tagInfo)}, m_name{std::move(tagInfo.m_name)}, m_count{tagInfo.m_count} {
    tagInfo.m_count = -1;
}

TagInfo::~TagInfo() {}

TagInfo& TagInfo::operator=(const TagInfo& tagInfo) {
    if (this == &tagInfo) {
        return *this;
   }

    BaseResult::operator=(tagInfo);

    m_name = tagInfo.m_name;
    m_count = tagInfo.m_count;

    return *this;
}

TagInfo& TagInfo::operator=(TagInfo&& tagInfo) {
    if (this == &tagInfo) {
        return *this;
   }

    BaseResult::operator=(std::forward<BaseResult>(tagInfo));

    m_name = std::move(tagInfo.m_name);
    m_count = tagInfo.m_count;
    tagInfo.m_count = -1;

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

}
