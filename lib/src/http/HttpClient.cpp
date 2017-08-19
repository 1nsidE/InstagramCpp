//
// Created by inside on 4/23/16.
//
#include <limits>
#include <cstring>

#include "sockets/SSLSocket.h"
#include "HttpClient.h"
#include "FormData.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

#include "exceptions/HttpFailedToRecieve.h"
#include "exceptions/HttpFailedToSend.h"
#include "exceptions/HttpTooBigResponse.h"

namespace Http {

HttpClient::HttpClient(){
    m_hostToSocketMap.max_load_factor(0.75);
}

HttpClient::HttpClient(HttpClient&& httpClient) : HttpClient{}{
    swap(*this, httpClient);
}

HttpClient::~HttpClient() {}

HttpClient& HttpClient::operator=(HttpClient&& client){
    m_hostToSocketMap = std::move(client.m_hostToSocketMap);
    return *this;
}

HttpResponse HttpClient::get(const HttpUrl& url){
    HttpRequest httpRequest = getDefaultRequest();
    httpRequest.setMethod(Method::GET);
    httpRequest.setUrl(url);

    return sendRequest(httpRequest);
}

HttpResponse HttpClient::post(const HttpUrl& url, const std::string& data, const std::string& content_type) {
    HttpRequest httpRequest = getDefaultRequest();
    httpRequest.setMethod(Method::POST);
    httpRequest.setUrl(url);
    httpRequest.setBody(data);
    httpRequest[Header::CONTENT_TYPE] = content_type;
    httpRequest[Header::CONTENT_LENGTH] = std::to_string(data.size());

    return sendRequest(httpRequest);
}

HttpResponse HttpClient::post(const HttpUrl& url, const FormData& form_data) {
    return post(url, form_data.getString(), form_data.contentType());
}

HttpResponse HttpClient::post(const HttpUrl& url, const std::pair<std::string, std::string>& type_and_data) {
    HttpRequest httpRequest = getDefaultRequest();
    httpRequest.setMethod(Method::POST);
    httpRequest.setUrl(url);
    httpRequest[Header::CONTENT_TYPE] = type_and_data.first;
    httpRequest.setBody(type_and_data.second);
    httpRequest[Header::CONTENT_LENGTH] = std::to_string(type_and_data.second.size());

    return sendRequest(httpRequest);
}

HttpResponse HttpClient::del(const HttpUrl& url) {
    HttpRequest request = getDefaultRequest();
    request.setMethod(Method::DELETE);
    request.setUrl(url);

    return sendRequest(request);
}

HttpRequest HttpClient::getDefaultRequest() const {
    HttpRequest httpRequest {};
    httpRequest[Header::USER_AGENT] = "http_client";
    httpRequest[Header::CONNECTION] = "keep-alive";
    httpRequest[Header::ACCEPT_ENCODING] = "*/*";

    return httpRequest;
}

HttpResponse HttpClient::sendRequest(const HttpRequest& httpRequest){
    HttpResponse response{};
    try{
        send(httpRequest);
        response = receive(httpRequest.getUrl(), 20);

        if (response[Header::CONNECTION] == "close") {
            disconnect(httpRequest.getUrl());
        }
    }catch(const std::exception& err){
        std::string errMsg = "Internal client error : ";
        response.setStatus(errMsg + err.what(), -1);
    }catch(...){
        response.setStatus("Unknown client error", -1);
    }

    return response;
}

HttpResponse HttpClient::operator<<(const HttpRequest &httpRequest) {
    return sendRequest(httpRequest);
}

HttpResponse HttpClient::operator<<(const HttpUrl& url) {
    return get(url);
}

void HttpClient::send(const HttpRequest& httpRequest) {
    const std::string& str = httpRequest.getString();
    const char* request = str.c_str();
    const size_t length = str.length();

    SocketPtr socket = getSocket(httpRequest.getUrl());
    if(!socket){
        return;
    }

    size_t written = 0;
    while (written < length) {
        long count = socket->write(request + written, length - written);
        if (count < 0) {
            switch (socket->lastError()) {
            case Socket::Error::INTERRUPTED:
                continue;
            default:
                std::string errMsg = "Failed to send data : ";
                errMsg += socket->lastErrorString();
                throw HttpFailedToSend(errMsg);
            }
        }

        written += static_cast<size_t>(count);
    }
}

HttpResponse HttpClient::receive(const HttpUrl& url, unsigned int timeout) {
    std::string response = read(url, timeout);
    
    int retry_count = 3;
    while (response.find("\r\n\r\n") == std::string::npos && retry_count) {
        response.append(read(url, timeout));
        --retry_count;
    }

    HttpResponse httpResponse = response;

    if (httpResponse.code() == Status::UNKNOWN) {
        return httpResponse;
    }
    
    size_t contentLen = httpResponse.contentLen();

    if (contentLen >= std::numeric_limits<unsigned int>::max()) {
        throw HttpTooBigResponse { "server response is too big!" };
    }

    size_t actual_contentLen = httpResponse.bodySize();
    while (contentLen > actual_contentLen) {
        const std::string& data = read(url, timeout);
        actual_contentLen += data.length();
        httpResponse.appendBody(data);
    }

    return httpResponse;
}

std::string HttpClient::read(const HttpUrl& url, unsigned int timeout) {
    std::string result {};
    
    SocketPtr socket = getSocket(url);
    if(!socket){
        return "";
    }

    if (socket->waitForRead(timeout)) {
        const static unsigned int buffSize = 1024;
        char buff[buffSize] = {};
        while (long count = socket->read(buff, buffSize)) {
            if (count < 0) {
                switch (socket->lastError()) {
                case Socket::Error::WOULDBLOCK:
                    return result;
                case Socket::Error::INTERRUPTED:
                    continue;
                default:
                    std::string errMsg = "Failed to recieve data : ";
                    errMsg += socket->lastErrorString();
                    throw HttpFailedToRecieve(errMsg);
                }
            }

            result.append(buff, static_cast<size_t>(count));
        }
    }

    return result;
}

HttpClient::SocketPtr HttpClient::connect(const HttpUrl& url) {
    HttpProtocol httpProtocol = url.protocol();   
    const std::string& host = url.host();
    
    SocketPtr socket{};

    switch (httpProtocol) {
    case HttpProtocol::HTTPS:
        socket = std::make_shared<Socket::SSLSocket>(host, toString(httpProtocol));
        break;
    case HttpProtocol::HTTP:
        socket = std::make_shared<Socket::TCPSocket>(host, toString(httpProtocol));
        break;
    case HttpProtocol::UNKNOWN:
        break;

    }
    
    if(socket){
        socket->makeNonBlocking();
    }
    return socket;
}

void HttpClient::disconnect(const HttpUrl& url) {
    m_hostToSocketMap.erase(url.host());
}

HttpClient::SocketPtr HttpClient::getSocket(const HttpUrl& url){
    std::string host = toString(url.protocol()) + (':' + url.host());

    HostToSocketMap::const_iterator it = m_hostToSocketMap.find(host);

    SocketPtr socket{nullptr};
    if(it == m_hostToSocketMap.end()){
        socket = connect(url);
        m_hostToSocketMap[host] = socket;
    }else{
        socket = m_hostToSocketMap[host];
    }
    
    return socket;
}

void swap(HttpClient& first, HttpClient& second){
    using std::swap;
    swap(first.m_hostToSocketMap, second.m_hostToSocketMap);
}

}
