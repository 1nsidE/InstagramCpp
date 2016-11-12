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
    HttpRequest http_request = get_default_request();
    http_request.set_method(Method::GET);
    http_request.set_url(url);

    return send_request(http_request);
}

HttpResponse HttpClient::post(const HttpUrl& url, const std::string& data, const std::string& content_type) {
    HttpRequest http_request = get_default_request();
    http_request.set_method(Method::POST);
    http_request.set_url(url);
    http_request.set_data(data);
    http_request[Header::CONTENT_TYPE] = content_type;
    http_request[Header::CONTENT_LENGTH] = std::to_string(data.size());

    return send_request(http_request);
}

HttpResponse HttpClient::post(const HttpUrl& url, const FormData& form_data) {
    return post(url, form_data.get_string(), form_data.get_content_type());
}

HttpResponse HttpClient::post(const HttpUrl& url, const std::pair<std::string, std::string>& type_and_data) {
    HttpRequest http_request = get_default_request();
    http_request.set_method(Method::POST);
    http_request.set_url(url);
    http_request[Header::CONTENT_TYPE] = type_and_data.first;
    http_request.set_data(type_and_data.second);
    http_request[Header::CONTENT_LENGTH] = std::to_string(type_and_data.second.size());

    return send_request(http_request);
}

HttpResponse HttpClient::del(const HttpUrl& url) {
    HttpRequest request = get_default_request();
    request.set_method(Method::DELETE);
    request.set_url(url);

    return send_request(request);
}

HttpRequest HttpClient::get_default_request() {
    HttpRequest http_request {};
    http_request[Header::USER_AGENT] = "http_client";
    http_request[Header::CONNECTION] = "keep-alive";
    http_request[Header::ACCEPT_ENCODING] = "*/*";

    return http_request;
}

HttpResponse HttpClient::send_request(const HttpRequest& http_request) {
    HttpResponse response{};
    try{
        send(http_request);
        response = receive(http_request.get_url(), 20);

        if (response[Header::CONNECTION] == "close") {
            disconnect(http_request.get_url());
        }
    }catch(const std::exception& err){
        std::string errMsg = "Internal client error : ";
        response.set_status(errMsg + err.what(), -1);
    }catch(...){
        response.set_status("Unknown client error", -1);
    }

    return response;
}

HttpResponse HttpClient::operator<<(const HttpRequest &http_request) {
    return send_request(http_request);
}

HttpResponse HttpClient::operator<<(const HttpUrl& url) {
    return get(url);
}

void HttpClient::send(const HttpRequest& http_request) {
    const std::string& str = http_request.get_string();
    const char* request = str.c_str();
    const size_t length = str.length();

    SocketPtr socket = get_socket(http_request.get_url());
    if(!socket){
        return;
    }

    size_t written = 0;
    while (written < length) {
        long count = socket->write(request + written, length - written);
        if (count < 0) {
            switch (socket->get_last_err()) {
            case Socket::Error::INTERRUPTED:
                continue;
            default:
                std::string err_msg = "Failed to send data : ";
                err_msg += socket->get_last_err_str();
                throw HttpFailedToSend(err_msg);
            }
        }

        written += static_cast<size_t>(count);
    }
}

HttpResponse HttpClient::receive(const HttpUrl& url, unsigned int timeout) {
    std::string response = read(url, timeout);

    HttpResponse http_response = response;
    if (http_response.get_code() == Status::UNKNOWN) {
        int retry_count = 3;
        while (retry_count && http_response.get_code() == Status::UNKNOWN) {
            response.append(read(url, timeout));
            http_response = response;
            --retry_count;
        }
    }

    if (http_response.get_code() == Status::UNKNOWN) {
        return http_response;
    }
    
    size_t content_len = http_response.content_len();

    if (content_len >= std::numeric_limits<unsigned int>::max()) {
        throw HttpTooBigResponse { "server response is too big!" };
    }

    size_t actual_content_len = http_response.data_len();
    while (content_len > actual_content_len) {
        const std::string& data = read(url, timeout);
        actual_content_len += data.length();
        http_response.append_data(data);
    }

    return http_response;
}

std::string HttpClient::read(const HttpUrl& url, unsigned int timeout) {
    std::string result {};
    
    SocketPtr socket = get_socket(url);
    if(!socket){
        return "";
    }

    if (socket->wait_for_read(timeout)) {
        const static unsigned int buff_size = 1024;
        char buff[buff_size] = {};
        while (long count = socket->read(buff, buff_size)) {
            if (count < 0) {
                switch (socket->get_last_err()) {
                case Socket::Error::WOULDBLOCK:
                    return result;
                case Socket::Error::INTERRUPTED:
                    continue;
                default:
                    std::string err_msg = "Failed to recieve data : ";
                    err_msg += socket->get_last_err_str();
                    throw HttpFailedToRecieve(err_msg);
                }
            }

            result.append(buff, static_cast<size_t>(count));
            std::memset(buff, 0, buff_size);
        }
    }

    return result;
}

HttpClient::SocketPtr HttpClient::connect(const HttpUrl& url) {
    
    const std::string& host = url.get_host();
    
    SocketPtr socket{};
    HttpProtocol httpProtocol = url.get_protocol();
    switch (httpProtocol) {
    case HttpProtocol::HTTPS:
        socket = std::make_shared<Socket::SSLSocket>(host, to_string(httpProtocol));
        break;
    case HttpProtocol::HTTP:
        socket = std::make_shared<Socket::TCPSocket>(host, to_string(httpProtocol));
        break;
    case HttpProtocol::UNKNOWN:
        break;

    }
    
    if(socket){
        socket->make_non_blocking();
    }
    return socket;
}

void HttpClient::disconnect(const HttpUrl& url) {
    m_hostToSocketMap.erase(url.get_host());
}

HttpClient::SocketPtr HttpClient::get_socket(const HttpUrl& url){
    const std::string& host = url.get_host();
    
    SocketPtr socket = m_hostToSocketMap[host];
    if(!socket){
        socket = connect(url);
        m_hostToSocketMap[host] = socket;
    }
    
    return socket;
}

}
