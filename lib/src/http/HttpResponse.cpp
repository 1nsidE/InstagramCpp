#include <sstream>
#include "HttpResponse.h"

namespace Http {

HttpResponse::HttpResponse() : HttpHeader {} {}

HttpResponse::HttpResponse(const std::string& response) : HttpHeader{} {
    parseResponse(response);
}

HttpResponse::HttpResponse(const HttpResponse& response) : HttpHeader { response }, m_status { response.m_status }, m_code { response.m_code } {}

HttpResponse::HttpResponse(HttpResponse&& response) : HttpResponse{} {
    swap(*this, response);
}

HttpResponse::~HttpResponse() {}

HttpResponse &HttpResponse::operator=(const HttpResponse& httpResponse) {
    HttpResponse copy{httpResponse};

    swap(*this, copy);
    return *this;
}

HttpResponse &HttpResponse::operator=(HttpResponse &&httpResponse) {
    swap(*this, httpResponse);

    HttpResponse temp{};
    swap(httpResponse, temp);
    return *this;
}

HttpResponse& HttpResponse::operator=(const std::string& response){
    parseResponse(response);
    return *this;
}

void HttpResponse::setStatus(Http::Status status) {
    m_status = toString(status);
    m_code = static_cast<int>(status);
}

void HttpResponse::setStatus(const std::string& status, int code) {
    m_status = status;
    m_code = code;
}

std::string HttpResponse::getString() const {
    std::string result{};
    result.append(HTTP_1_1).append(" ").append(m_status).append(" ").append(std::to_string(m_code)).append(CRLF);

    result.append(HttpHeader::getString());
    return result;
}

const std::string& HttpResponse::status() const noexcept {
    return m_status;
}

int HttpResponse::code() const noexcept {
    return m_code;
}

void HttpResponse::parseResponse(const std::string& response){
    if (response.empty()) {
        return;
    }

    std::istringstream stringStream(response);
    std::string line {};

    std::getline(stringStream, line);
    std::vector<std::string> tokens = split(line, ' ');

    if (tokens.size() < 3) {
        return;
    }

    setStatus(tokens[2], std::stoi(tokens[1]));

    while (std::getline(stringStream, line)) {
        if (!line.compare("\r")) {
            break;
        }
        const std::vector<std::string> headerPair = split(line, ':', true);
        if(headerPair.size() != 2){
            throw std::runtime_error("invalid header: " + line);
        }
        addHeader(headerPair[0], headerPair[1]);
    }
 
    std::streampos pos{stringStream.tellg()};
    if (pos >= 0 && static_cast<std::size_t>(pos) < response.length()) {
        setBody(response.substr(pos, response.length() - pos));
    }
}

void swap(HttpResponse& first, HttpResponse& second){
    using std::swap;
    swap(static_cast<HttpHeader&>(first), static_cast<HttpHeader&>(second));

    swap(first.m_status, second.m_status);
    swap(first.m_code, second.m_code);
}

}
