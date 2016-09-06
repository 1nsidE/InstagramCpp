//
// Created by inside on 4/23/16.
//
#include <limits>

#include "TCPSocket.h"
#include "SSLSocket.h"
#include "HttpHeaderParser.h"
#include "HttpClient.h"

#include "exceptions/HttpFailedToRecieve.h"
#include "exceptions/HttpFailedToSend.h"
#include "exceptions/HttpTooBigResponse.h"

namespace Http {

HttpClient::HttpClient(const std::string &_host, HttpProtocol _protocol) : socket { nullptr }, host { _host }, protocol { _protocol }, connected { false } {    }

HttpClient::HttpClient(HttpClient&& http_client) : socket { std::move(http_client.socket) }, host { std::move(http_client.host) }, protocol { http_client.protocol }, connected { http_client.connected } {
    http_client.socket = nullptr;
    http_client.connected = false;
}

HttpClient::~HttpClient() {
    if (socket != nullptr) {
        delete socket;
    }
}

HttpResponse HttpClient::get(const HttpUrl& url) {
    HttpRequest http_request = get_standart_request();;
    http_request.set_method(Method::GET);
    http_request.set_url(url);

    return send_request(http_request);
}

HttpResponse HttpClient::post(const HttpUrl& url, const std::string& data, const std::string& content_type) {
    HttpRequest http_request = get_standart_request();
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
    HttpRequest http_request = get_standart_request();
    http_request.set_method(Method::POST);
    http_request.set_url(url);
    http_request[Header::CONTENT_TYPE] = type_and_data.first;
    http_request.set_data(type_and_data.second);
    http_request[Header::CONTENT_LENGTH] = std::to_string(type_and_data.second.size());

    return send_request(http_request);
}

HttpResponse HttpClient::del(const HttpUrl& url) {
    HttpRequest request = get_standart_request();
    request.set_method(Method::DELETE);
    request.set_url(url);

    return send_request(request);
}

HttpRequest HttpClient::get_standart_request() {
    HttpRequest http_request {};
    http_request[Header::USER_AGENT] = STANDART_USER_AGENT;
    http_request[Header::CONNECTION] = "keep-alive";
    http_request[Header::ACCEPT_ENCODING] = "*/*";
    http_request[Header::HOST] = host;

    return http_request;
}

HttpResponse HttpClient::send_request(const HttpRequest& http_request) {
    if (!connected) {
        connect();
    }

    send(http_request);
    HttpResponse http_response = recieve(20);

    if (http_response[Header::CONNECTION] == "close") {
        disconnect();
    }

    return http_response;
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

HttpResponse HttpClient::recieve(unsigned int timeout) {
    std::string response = read(timeout);

    HttpResponse http_response = HttpHeaderParser::parse_response(response);
    if (http_response.get_code() == Status::UNKNOWN) {
        int retry_count = 3;
        while (retry_count && http_response.get_code() == Status::UNKNOWN) {
            response.append(read(timeout));
            http_response = HttpHeaderParser::parse_response(response);
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
        const std::string& data = read(timeout);
        actual_content_len += data.length();
        http_response.append_data(data);
    }

    return http_response;
}

std::string HttpClient::read(unsigned int timeout) {
    std::string result {};

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

void HttpClient::connect() {
    if (connected) {
        disconnect();
    }

    switch (protocol) {
    case HttpProtocol::HTTPS:
        socket = new Socket::SSLSocket(host, "https");
        break;
    case HttpProtocol::HTTP:
        socket = new Socket::TCPSocket(host, "http");
        break;
    }
    socket->make_non_blocking();
    connected = true;
}

void HttpClient::disconnect() {
    if (socket != nullptr) {
        socket->close();
        delete socket;
        socket = nullptr;
    }
    connected = false;
}

}
