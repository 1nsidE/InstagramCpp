#ifndef BASE_RESULT_H
#define BASE_RESULT_H

#include <string>

namespace Instagram{

class BaseResult{
public:
	BaseResult();
    BaseResult(const char* _err_msg);
	BaseResult(const std::string& _err_msg);
	
	BaseResult(const BaseResult& base_result);
	BaseResult(BaseResult&& base_result);

	virtual ~BaseResult();
    
    BaseResult& operator=(const BaseResult& base_result);
    BaseResult& operator=(BaseResult&& base_result);

	const std::string& get_error_message() const;
	bool is_succeed();
private:
	std::string* err_msg;
};

}

#endif
