//
// Created by inside on 4/23/16.
//
#include <limits>

#include "SSLSocket.h"
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

HttpClient::HttpClient(HttpClient&& http_client) : m_hostToSocketMap {std::move(http_client.m_hostToSocketMap)}{}

HttpClient::~HttpClient() {}

HttpResponse HttpClient::get(const HttpUrl& url) {
    HttpRequest httpRequest = getDefaultRequest();
    httpRequest.setMethod(Method::GET);
    httpRequest.setUrl(url);

    return sendRequest(httpRequest);
}

HttpResponse HttpClient::post(const HttpUrl& url, const std::string& data, const std::string& content_type) {
    HttpRequest httpRequest = getDefaultRequest();
    httpRequest.setMethod(Method::POST);
    httpRequest.setUrl(url);
    httpRequest.setData(data);
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
    httpRequest.setData(type_and_data.second);
    httpRequest[Header::CONTENT_LENGTH] = std::to_string(type_and_data.second.size());

    return sendRequest(httpRequest);
}

HttpResponse HttpClient::del(const HttpUrl& url) {
    HttpRequest request = getDefaultRequest();
    request.setMethod(Method::DELETE);
    request.setUrl(url);

    return sendRequest(request);
}

HttpRequest HttpClient::getDefaultRequest() {
    HttpRequest httpRequest {};
    httpRequest[Header::USER_AGENT] = "http_client";
    httpRequest[Header::CONNECTION] = "keep-alive";
    httpRequest[Header::ACCEPT_ENCODING] = "*/*";

    return httpRequest;
}

HttpResponse HttpClient::sendRequest(const HttpRequest& httpRequest) {
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

    HttpResponse httpResponse = response;
    if (httpResponse.code() == Status::UNKNOWN) {
        int retry_count = 3;
        while (retry_count && httpResponse.code() == Status::UNKNOWN) {
            response.append(read(url, timeout));
            httpResponse = response;
            --retry_count;
        }
    }

    if (httpResponse.code() == Status::UNKNOWN) {
        return httpResponse;
    }
    
    size_t contentLen = httpResponse.contentLen();

    if (contentLen >= std::numeric_limits<unsigned int>::max()) {
        throw HttpTooBigResponse { "server response is too big!" };
    }

    size_t actual_contentLen = httpResponse.dataLen();
    while (contentLen > actual_contentLen) {
        const std::string& data = read(url, timeout);
        actual_contentLen += data.length();
        httpResponse.appendData(data);
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
            std::memset(buff, 0, buffSize);
        }
    }

    return result;
}

HttpClient::SocketPtr HttpClient::connect(const HttpUrl& url) {
    
    const std::string& host = url.host();
    
    SocketPtr socket{};
    HttpProtocol httpProtocol = url.protocol();
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
    const std::string& host = url.host();
    
    SocketPtr socket = m_hostToSocketMap[host];
    if(!socket){
        socket = connect(url);
        m_hostToSocketMap[host] = socket;
    }
    
    return socket;
}

}
