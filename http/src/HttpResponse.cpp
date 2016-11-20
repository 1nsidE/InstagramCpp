#include <sstream>
#include "HttpResponse.h"

namespace Http {

HttpResponse::HttpResponse() : HttpHeader {} {}

HttpResponse::HttpResponse(const std::string& response) : HttpHeader{} {
    parseResponse(response);
}

HttpResponse::HttpResponse(const HttpResponse& response) : HttpHeader { response }, m_status { response.m_status }, m_code { response.m_code } {}
HttpResponse::HttpResponse(HttpResponse&& response) : HttpHeader { std::forward<HttpHeader>(response) }, m_status { std::move(response.m_status) }, m_code { response.m_code } {
    response.m_code = -1;
}

HttpResponse::~HttpResponse() {}

HttpResponse &HttpResponse::operator=(const HttpResponse& httpResponse) {
    if (this != &httpResponse) {
        HttpHeader::operator=(httpResponse);
        m_status = httpResponse.m_status;
    }
    return *this;
}

HttpResponse &HttpResponse::operator=(HttpResponse &&httpResponse) {
    if (this != &httpResponse) {
        HttpHeader::operator=(std::forward<HttpHeader>(httpResponse));
        m_status = std::move(httpResponse.m_status);

        m_code = httpResponse.m_code;
        httpResponse.m_code = -1;
    }
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
    std::string result("");
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
    std::vector<std::string> tokens = tokenize(line, ' ');

    if (tokens.size() < 3) {
        return;
    }

    setStatus(tokens[2], std::stoi(tokens[1]));

    while (std::getline(stringStream, line)) {
        if (!line.compare("\r")) {
            break;
        }
        addHeader(line);
    }
 
    size_t pos;
    if ((pos = static_cast<size_t>(stringStream.tellg())) < response.length()) {
        setData(response.substr(pos, response.length() - pos));
    }
}

}
