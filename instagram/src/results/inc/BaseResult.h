#ifndef BASE_RESULT_H
#define BASE_RESULT_H

#include <string>
#include "InstagramDefinitions.h"

namespace  Instagram{
    class EXPORT_INSTAGRAM BaseResult{
    public:
        BaseResult();
        BaseResult(const char* _err_msg);
        BaseResult(const std::string& _err_msg);

        BaseResult(const BaseResult& base_result);
        BaseResult(BaseResult&& base_result);

        virtual ~BaseResult();

        BaseResult& operator=(const BaseResult& base_result);
        BaseResult& operator=(BaseResult&& base_result);

        explicit operator bool() const noexcept;

        const std::string& get_error_message() const noexcept;
        bool is_succeed() const noexcept;
    private:
        std::string* err_msg;
    };

}

#endif
