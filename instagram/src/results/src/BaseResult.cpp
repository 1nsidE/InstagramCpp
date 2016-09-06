//
// Created by inside on 4/30/16.
//

#include <stdexcept>
#include "BaseResult.h"

namespace Instagram {

    BaseResult::BaseResult() : err_msg(nullptr) {}

    BaseResult::BaseResult(const char *_err_msg) {
        if (_err_msg == nullptr) {
            throw std::invalid_argument("err_msg cannot be null");
        }

        err_msg = new std::string{ _err_msg };
    }

    BaseResult::BaseResult(const std::string &_err_msg) {
        err_msg = new std::string{ _err_msg };
    }

    BaseResult::BaseResult(BaseResult&& base_result) : err_msg{ base_result.err_msg } {
        base_result.err_msg = nullptr;
    }

    BaseResult::BaseResult(const BaseResult& base_result) {
        err_msg = nullptr;
        if (base_result.err_msg != nullptr) {
            err_msg = new std::string{ *base_result.err_msg };
        }
    }

    BaseResult::~BaseResult() {
        if (err_msg) {
            delete err_msg;
            err_msg = nullptr;
        }
    }

    BaseResult& BaseResult::operator=(const BaseResult& base_result) {
        if (this == &base_result) {
            return *this;
        }

        if (err_msg != nullptr) {
            delete err_msg;
        }

        err_msg = nullptr;
        if (base_result.err_msg != nullptr) {
            err_msg = new std::string{ *base_result.err_msg };
        }

        return *this;
    }

    BaseResult& BaseResult::operator=(BaseResult&& base_result) {
        if (this == &base_result) {
            return *this;
        }

        if (err_msg != nullptr) {
            delete err_msg;
        }

        err_msg = base_result.err_msg;
        base_result.err_msg = nullptr;

        return *this;
    }

    BaseResult::operator bool() const noexcept {
        return is_succeed();
    }

    const std::string& BaseResult::get_error_message() const noexcept {
        const static std::string empty_error{ "" };
        return err_msg ? *err_msg : empty_error;
    }

    bool BaseResult::is_succeed() const noexcept {
        return err_msg == nullptr;
    }

}
