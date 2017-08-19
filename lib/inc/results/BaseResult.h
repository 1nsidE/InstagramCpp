#ifndef BASE_RESULT_H
#define BASE_RESULT_H

#include <string>
#include <memory>
#include "InstagramDefinitions.h"

namespace  Instagram{
class EXPORT_INSTAGRAM BaseResult{
public:
    BaseResult();
    BaseResult(const char* errMsg);
    BaseResult(const std::string& errMsg);

    BaseResult(const BaseResult& baseResult);
    BaseResult(BaseResult&& baseResult);

    virtual ~BaseResult();

    BaseResult& operator=(const BaseResult& baseResult);
    BaseResult& operator=(BaseResult&& baseResult);

    explicit operator bool() const noexcept;

    const std::string& errorMessage() const noexcept;
    bool succeed() const noexcept;
private:
    using ErrPtr = std::unique_ptr<std::string>;
    ErrPtr m_errMsg;

    friend void swap(BaseResult& result1, BaseResult& result2);
};

}

#endif
