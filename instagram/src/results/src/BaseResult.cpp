//
// Created by inside on 4/30/16.
//

#include <stdexcept>
#include "BaseResult.h"

namespace Instagram{

BaseResult::BaseResult(const std::string &_err_msg) {
    err_msg = new std::string{_err_msg};
}

BaseResult::BaseResult(BaseResult &&base_result) : err_msg(base_result.err_msg) {
    base_result.err_msg = nullptr;
}

BaseResult::BaseResult(const BaseResult &base_result) {
    if(base_result.err_msg != nullptr){
        err_msg = new std::string{*base_result.err_msg};
    }
}

BaseResult::BaseResult(const char *_err_msg) {
    if(_err_msg == nullptr){
        throw std::invalid_argument("err_msg cannot be null");
    }

    err_msg = new std::string{_err_msg};
}

BaseResult::~BaseResult() {
    if(err_msg != nullptr){
        delete err_msg;
    }
}

const std::string * BaseResult::get_error_message() {
    return err_msg;
}

bool BaseResult::is_succeed() {
    return err_msg == nullptr;
}

}
