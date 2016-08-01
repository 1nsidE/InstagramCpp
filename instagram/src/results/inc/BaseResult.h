#ifndef BASE_RESULT_H
#define BASE_RESULT_H

#include <string>
#include <xstring>
#include "InstagramDefinitions.h"

namespace  Instagram{
    EXPIMP_TEMPLATE template struct EXPORT_INSTAGRAM std::char_traits<char>;
    EXPIMP_TEMPLATE template class EXPORT_INSTAGRAM std::allocator<char>;
    EXPIMP_TEMPLATE template class EXPORT_INSTAGRAM std::basic_string<char, std::char_traits<char>, std::allocator<char>>;

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
