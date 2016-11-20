//
// Created by inside on 4/30/16.
//

#include <stdexcept>
#include "BaseResult.h"

namespace Instagram {

BaseResult::BaseResult() {}

BaseResult::BaseResult(const char *errMsg) {
    if (errMsg == nullptr) {
        throw std::invalid_argument("err_msg cannot be null");
    }

    m_errMsg = std::make_unique<std::string>(errMsg);
}

BaseResult::BaseResult(const std::string& errMsg) {
    m_errMsg = std::make_unique<std::string>(std::string{errMsg});
}

BaseResult::BaseResult(BaseResult&& baseResult) : m_errMsg{std::move(baseResult.m_errMsg)} {}

BaseResult::BaseResult(const BaseResult& baseResult) {
    if (baseResult.m_errMsg) {
        m_errMsg = std::make_unique<std::string>(*baseResult.m_errMsg);
    }
}

BaseResult::~BaseResult() {}

BaseResult& BaseResult::operator=(const BaseResult& baseResult) {
    if (this == &baseResult) {
        return *this;
    }

    if (m_errMsg) {
        m_errMsg.reset();
    }

    if (baseResult.m_errMsg) {
        m_errMsg = std::make_unique<std::string>(*baseResult.m_errMsg);
    }

    return *this;
}

BaseResult& BaseResult::operator=(BaseResult&& baseResult) {
    if (this == &baseResult) {
        return *this;
    }

    m_errMsg = std::move(baseResult.m_errMsg);

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

}
