//
// Created by inside on 3/12/16.
//

#include<sstream>
#include "HttpRequest.h"

namespace Http {

HttpRequest::HttpRequest() : HttpHeader {}, m_method(Http::Method::UNKNOWN) {}

HttpRequest::HttpRequest(const HttpRequest& request) : HttpHeader {request}, m_method {request.m_method}, m_url{request.m_url} {}

HttpRequest::HttpRequest(HttpRequest&& request) : HttpRequest{} {
    swap(*this, request);
} 

HttpRequest::HttpRequest(const HttpUrl& url, Method method) : HttpHeader{}, m_method{method}, m_url{url}{
    setHost(url.host());
}

HttpRequest::HttpRequest(HttpUrl &&url, Method method) : HttpHeader{}, m_method{method}, m_url{std::move(url)} {
    setHost(url.host());
}

HttpRequest::HttpRequest(const std::string& request){
    parse(request);
}

HttpRequest::~HttpRequest(){}

HttpRequest& HttpRequest::operator=(const HttpRequest& httpRequest) {
    HttpRequest copy{httpRequest};

    swap(*this, copy);
    return *this;
}

HttpRequest& HttpRequest::operator=(HttpRequest&& httpRequest) {
    swap(*this, httpRequest);

    HttpRequest temp{};
    swap(httpRequest, temp);
    return *this;
}

void HttpRequest::setMethod(Http::Method method) {
    m_method = method;
}

Http::Method HttpRequest::method() const {
    return m_method;
}

std::string HttpRequest::getString() const {
    if (m_method == Http::Method::UNKNOWN) {
        return "";
    }

    std::string result { toString(m_method) };
    result += " " + m_url.endpoint() + ARG_START_DELIMETER + m_url.arguments() + " " + HTTP_1_1 + CRLF;

    result += HttpHeader::getString();
    return result;
}

void HttpRequest::setUrl(const HttpUrl& url) {
    m_url = url;
    setHost(url.host());
}

void HttpRequest::setUrl(HttpUrl&& url) {
    m_url = std::move(url);
    setHost(m_url.host());
}

const HttpUrl& HttpRequest::getUrl() const noexcept {
    return m_url;
}

void HttpRequest::parse(const std::string& request){
    if (request.empty()) {
        return;
    }

    std::istringstream stringStream{request};
    std::string line {};

    std::getline(stringStream, line);
    std::vector<std::string> tokens = split(line, ' ');
    if (tokens.size() != 3) {
        throw std::runtime_error("invalid request header: " + line);
    }
    
    setMethod(fromStr(tokens[0]));
    setUrl(getHeader(Header::HOST) + tokens[1]);

    while (std::getline(stringStream, line)) {
        if (!line.compare("\r")) {
            break;
        }
        const std::vector<std::string> headerPair = split(line, ':', true);
        if(headerPair.size() != 2){
            throw std::runtime_error("invalid header: " + line);
        }
        addHeader(tokens[0], tokens[1]);
    }

    std::streampos pos{stringStream.tellg()};
    if (pos >= 0 && static_cast<std::size_t>(pos) < request.length()) {
        setBody(request.substr(pos, request.length() - pos));
    }
}

void swap(HttpRequest& first, HttpRequest& second){
    using std::swap;
    swap(static_cast<HttpHeader&>(first), static_cast<HttpHeader&>(second));

    swap(first.m_url, second.m_url);
    swap(first.m_method, second.m_method);
}

}
