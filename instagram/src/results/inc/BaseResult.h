#ifndef BASE_RESULT_H
#define BASE_RESULT_H

#include <string>

#ifdef WIN32
#include<xstring>
#ifdef INSTAGRAM_LIB_EXPORT
#define EXPORT_INSTAGRAM __declspec(dllexport)
#define EXPIMP_TEMPLATE
#else
#define EXPORT_INSTAGRAM __declspec(dllimport)
#define EXPIMP_TEMPLATE extern
#endif

#else
#ifdef __linux__
#define EXPORT_INSTAGRAM
#define EXPIMP_TEMPLATE
#endif
#endif

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
