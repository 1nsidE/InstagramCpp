#ifndef HTTP_RESPONSE_HEADER
#define HTTP_RESPONSE_HEADER

#include "HttpHeader.h"

namespace Http{

	class EXPORT_HTTP HttpResponse : public HttpHeader{
	public:
		HttpResponse();
		HttpResponse(const HttpResponse& response);
		HttpResponse(HttpResponse&& response);

		virtual ~HttpResponse();

		HttpResponse& operator=(HttpResponse&& http_response);
		HttpResponse& operator=(const HttpResponse& http_response);

		const std::string& get_status() const noexcept;
		int get_code() const noexcept;
		void set_status(Http::Status _status);
		void set_status(const std::string& status, int code);

		virtual std::string get_string() const override;
	private:
		std::string status{};
		int code = -1;
	};

}
#endif
