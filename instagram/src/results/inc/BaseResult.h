#ifndef BASE_RESULT_H
#define BASE_RESULT_H

#include <string>
#include <memory>
#include "InstagramDefinitions.h"

namespace  Instagram{
class EXPORT_INSTAGRAM BaseResult{
public:
    BaseResult();
    BaseResult(const char* err_msg);
    BaseResult(const std::string& err_msg);

    BaseResult(const BaseResult& base_result);
    BaseResult(BaseResult&& base_result);

    virtual ~BaseResult();

    BaseResult& operator=(const BaseResult& base_result);
    BaseResult& operator=(BaseResult&& base_result);

    explicit operator bool() const noexcept;

    const std::string& get_error_message() const noexcept;
    bool is_succeed() const noexcept;
private:
    using ErrPtr = std::unique_ptr<std::string>;
    ErrPtr m_errMsg;
};

}

#endif
