//
// Created by inside on 4/30/16.
//

#include <stdexcept>
#include "BaseResult.h"

namespace Instagram {

BaseResult::BaseResult() {}

BaseResult::BaseResult(const char *err_msg) {
    if (err_msg == nullptr) {
        throw std::invalid_argument("err_msg cannot be null");
    }

    m_errMsg = std::make_unique<std::string>(err_msg);
}

BaseResult::BaseResult(const std::string& err_msg) {
    m_errMsg = std::make_unique<std::string>(std::string{err_msg});
}

BaseResult::BaseResult(BaseResult&& base_result) : m_errMsg{std::move(base_result.m_errMsg)} {}

BaseResult::BaseResult(const BaseResult& base_result) {
    if (base_result.m_errMsg) {
        m_errMsg = std::make_unique<std::string>(*base_result.m_errMsg);
    }
}

BaseResult::~BaseResult() {}

BaseResult& BaseResult::operator=(const BaseResult& base_result) {
    if (this == &base_result) {
        return *this;
    }

    if (m_errMsg) {
        m_errMsg.reset();
    }

    if (base_result.m_errMsg) {
        m_errMsg = std::make_unique<std::string>(*base_result.m_errMsg);
    }

    return *this;
}

BaseResult& BaseResult::operator=(BaseResult&& base_result) {
    if (this == &base_result) {
        return *this;
    }

    m_errMsg = std::move(base_result.m_errMsg);

    return *this;
}

BaseResult::operator bool() const noexcept {
    return is_succeed();
}

const std::string& BaseResult::get_error_message() const noexcept {
    const static std::string empty_error{ "" };
    return m_errMsg ? *m_errMsg : empty_error;
}

bool BaseResult::is_succeed() const noexcept {
    return m_errMsg == nullptr;
}

}
