//
// Created by inside on 3/12/16.
//

#include<sstream>
#include "HttpRequest.h"

namespace Http {

HttpRequest::HttpRequest() : HttpHeader {}, m_method(Http::Method::UNKNOWN) {}
HttpRequest::HttpRequest(const HttpRequest& request) : HttpHeader {request}, m_method {request.m_method}, m_url{request.m_url} {}
HttpRequest::HttpRequest(HttpRequest&& request) : HttpHeader {std::move(request)}, m_method {request.m_method}, m_url{std::move(request.m_url)} {}

HttpRequest::HttpRequest(const HttpUrl& url, Method method) : HttpHeader{}, m_method{method}, m_url{url}{
    set_host(url.get_host());
}

HttpRequest::HttpRequest(HttpUrl &&url, Method method) : HttpHeader{}, m_method{method}, m_url{std::move(url)} {
    set_host(url.get_host());
}

HttpRequest::HttpRequest(const std::string& request){
    parse(request);
}

HttpRequest::~HttpRequest(){}

HttpRequest& HttpRequest::operator=(const HttpRequest& http_request) {
    if (this == &http_request) {
        return *this;
    }
    HttpHeader::operator=(http_request);
    m_method = http_request.m_method;
    m_url = http_request.m_url;

    return *this;
}

HttpRequest& HttpRequest::operator=(HttpRequest&& http_request) {
    if (this == &http_request) {
        return *this;
    }
    HttpHeader::operator=(std::forward<HttpHeader>(http_request));
    
    m_method = http_request.m_method;
    http_request.m_method = Http::Method::UNKNOWN;
    
    m_url = std::move(http_request.m_url);
    
    return *this;
}

void HttpRequest::set_method(Http::Method method) {
    m_method = method;
}

Http::Method HttpRequest::get_method() const {
    return m_method;
}

std::string HttpRequest::get_string() const {
    if (m_method == Http::Method::UNKNOWN) {
        return "";
    }

    std::string result { to_string(m_method) };
    result += " " + m_url.get_endpoint() + ARG_START_DELIMETER + m_url.get_arguments() + " " + HTTP_1_1 + CRLF;

    result += HttpHeader::get_string();
    return result;
}

void HttpRequest::set_url(const HttpUrl& url) {
    m_url = url;
    set_host(url.get_host());
}


void HttpRequest::set_url(HttpUrl&& url) {
    m_url = std::move(url);
    set_host(m_url.get_host());
}

const HttpUrl& HttpRequest::get_url() const noexcept {
    return m_url;
}

void HttpRequest::parse(const std::string& request){
    if (request.empty()) {
        return;
    }

    std::istringstream string_stream(request);
    std::string line {};

    std::getline(string_stream, line);
    std::vector<std::string> tokens = tokenize(line, ' ');
    if (tokens.size() != 3) {
        throw std::runtime_error({ "invalid request header: " + line });
    }
    
    set_method(from_str(tokens[0]));

    HttpUrl url{tokens[1]};
    set_url(std::move(url));

    while (std::getline(string_stream, line)) {
        if (!line.compare("\r")) {
            break;
        }
        add_header(line);
    }
    
    size_t pos{0};
    if ((pos = static_cast<size_t>(string_stream.tellg())) < request.length()) {
        set_data(request.substr(pos, request.length() - pos));
    }
}

}
