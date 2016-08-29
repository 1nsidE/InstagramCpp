#include "HttpResponse.h"

namespace Http {

HttpResponse::HttpResponse() : HttpHeader {} {}

HttpResponse::HttpResponse(const HttpResponse& response) : HttpHeader { response }, status { response.status }, code { response.code } {}
HttpResponse::HttpResponse(HttpResponse&& response) : HttpHeader { std::forward<HttpHeader>(response) }, status { std::move(response.status) }, code { response.code } {
    response.code = -1;
}

HttpResponse::~HttpResponse() {}

HttpResponse &HttpResponse::operator=(const HttpResponse& http_response) {
    if (this != &http_response) {
        HttpHeader::operator=(http_response);
        status = http_response.status;
    }
    return *this;
}

HttpResponse &HttpResponse::operator=(HttpResponse &&http_response) {
    if (this != &http_response) {
        HttpHeader::operator=(std::forward<HttpHeader>(http_response));
        status = std::move(http_response.status);

        code = http_response.code;
        http_response.code = -1;
    }
    return *this;
}

void HttpResponse::set_status(Http::Status _status) {
    status = to_string(_status);
    code = static_cast<int>(_status);
}

void HttpResponse::set_status(const std::string& status_, int code_) {
    status = status_;
    code = code_;
}

std::string HttpResponse::get_string() const {
    std::string result("");
    result.append(HTTP_1_1).append(" ").append(status).append(" ").append(std::to_string(code)).append(CRLF);

    result.append(HttpHeader::get_string());
    return result;
}

const std::string& HttpResponse::get_status() const noexcept {
    return status;
}

int HttpResponse::get_code() const noexcept {
    return code;
}

}
