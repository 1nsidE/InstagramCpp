//
// Created by inside on 4/30/16.
//

#include <stdexcept>
#include "BaseResult.h"

namespace Instagram {

BaseResult::BaseResult() {}

BaseResult::BaseResult(const char *errMsg) {
    if (errMsg == nullptr) {
        throw std::invalid_argument("errMsg cannot be null");
    }

    m_errMsg = std::make_unique<std::string>(errMsg);
}

BaseResult::BaseResult(const std::string& errMsg) {
    m_errMsg = std::make_unique<std::string>(errMsg);
}

BaseResult::BaseResult(BaseResult&& baseResult) : BaseResult() {
    swap(*this, baseResult);
}

BaseResult::BaseResult(const BaseResult& baseResult) {
    if (baseResult.m_errMsg) {
        m_errMsg = std::make_unique<std::string>(*baseResult.m_errMsg);
    }
}

BaseResult::~BaseResult() {}

BaseResult& BaseResult::operator=(const BaseResult& baseResult) {
    BaseResult copy{baseResult};

    swap(*this, copy);
    return *this;
}

BaseResult& BaseResult::operator=(BaseResult&& baseResult) {
    swap(*this, baseResult);

    BaseResult temp{};
    swap(baseResult, temp); 
    return *this;
}

BaseResult::operator bool() const noexcept {
    return succeed();
}

const std::string& BaseResult::errorMessage() const noexcept {
    const static std::string emptyError{""};
    return m_errMsg ? *m_errMsg : emptyError;
}

bool BaseResult::succeed() const noexcept {
    return m_errMsg == nullptr;
}

void swap(BaseResult& result1, BaseResult& result2){
    using std::swap;
    swap(result1.m_errMsg, result2.m_errMsg);
}

}
