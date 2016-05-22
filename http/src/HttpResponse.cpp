#include "HttpResponse.h"

namespace Http{

HttpResponse::HttpResponse() : status(Http::Status::UNKNOWN){}

HttpResponse::HttpResponse(HttpResponse& response) : HttpHeader(response), status(response.status){}
HttpResponse::HttpResponse(HttpResponse&& response) : HttpHeader(response), status(response.status){
    response.status = Http::Status::UNKNOWN;
}

HttpResponse::~HttpResponse(){}

void HttpResponse::set_status(Http::Status _status){
    status = _status;
}

std::string HttpResponse::get_string() const{
    std::string result("");
    result.append(HTTP_1_1).append(" ").append(std::to_string(static_cast<int>(status))).append(" ").append(get_str(status)).append(CRLF);
    
    result.append(HttpHeader::get_string());
    return result;
}

Http::Status HttpResponse::get_status() const {
    return status;
}

HttpResponse &HttpResponse::operator=(HttpResponse &&http_response) {
    if(this != &http_response){
        HttpHeader::operator=(http_response);
        status = http_response.status;
        http_response.status = Http::Status::UNKNOWN;
    }
    return *this;
}


HttpResponse &HttpResponse::operator=(const HttpResponse& http_response) {
    if(this != &http_response){
        HttpHeader::operator=(http_response);
        status = http_response.status;

    }
    return *this;
}

}
