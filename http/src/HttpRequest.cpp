//
// Created by inside on 3/12/16.
//

#include "HttpRequest.h"

namespace Http{

HttpRequest::HttpRequest() : method(Http::Method::UNKNOWN){}
HttpRequest::HttpRequest(const HttpRequest& request) : HttpHeader{request}, method{request.method}, url{request.url}{}
HttpRequest::HttpRequest(HttpRequest&& request) : HttpHeader{request}, method{request.method}, url{std::move(request.url)}{}

HttpRequest::~HttpRequest() {}

HttpRequest& HttpRequest::operator=(const HttpRequest& http_request){
    if(this == &http_request){
        return *this;
    }
    HttpHeader::operator=(http_request);
    method = http_request.method;
    url = http_request.url;

    return *this;
}

HttpRequest& HttpRequest::operator=(HttpRequest&& http_request){
    if(this == &http_request){
        return *this;
    }
    HttpHeader::operator=(http_request);

    http_request.method = Http::Method::UNKNOWN;
    url = std::move(http_request.url);
    return *this;
}

void HttpRequest::set_method(Http::Method _method) {
    method = _method;
}

Http::Method HttpRequest::get_method() const{
    return method;
}

std::string HttpRequest::get_string() const {
    if(method == Http::Method::UNKNOWN){
        return "";
    }

    std::string result{get_str(method)};
    result += " " + url.get_url() + " " + HTTP_1_1 + CRLF;
    
    result += HttpHeader::get_string();
    return result;
}

void HttpRequest::set_url(const HttpUrl& _url){
    url = _url;
}

void HttpRequest::set_url(HttpUrl&& _url){
    url = _url;
}

}
