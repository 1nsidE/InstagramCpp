//
// Created by inside on 4/23/16.
//
#include <netdb.h>
#include <thread>

#include "TCPSocket.h"
#include "SSLSocket.h"
#include "HttpHeaderParser.h"
#include "HttpClient.h"

namespace Http{

HttpClient::HttpClient(const std::string &_host, HttpProtocol _protocol) : socket{nullptr}, host{_host}, protocol{_protocol}{
    connect();  
}

HttpClient::HttpClient(HttpClient &&http_socket) : socket{std::move(http_socket.socket)}, host{std::move(http_socket.host)}, protocol{http_socket.protocol} {
    http_socket.socket = nullptr;
}

HttpClient::~HttpClient(){
    if(socket != nullptr){
        delete socket;
    }
}

HttpResponse HttpClient::send_request(const HttpRequest& http_request){
    send(http_request); 
    HttpResponse http_response = recieve(20);
    
    if(http_response[Header::CONNECTION] == "close"){
        connect();
    }

    return http_response;
}

HttpResponse HttpClient::operator<<(const HttpRequest &http_request){
    return send_request(http_request);
}

void HttpClient::send(const HttpRequest& http_request) const{
    int written = 0;

    const std::string& str = http_request.get_string();
    const char* request = str.c_str();
    const size_t length = str.length();
    while(static_cast<size_t>(written) < length){
        int count = socket->write(request + written, length - static_cast<size_t>(written));
        if(count < 0){
            if(errno == EINTR){
                count = 0;
                continue;
            }else{
                std::string err_msg = "Failed to send data : ";
                err_msg += gai_strerror(errno);
                throw std::runtime_error(err_msg);
            }
        }
        written += count;
    }
}

HttpResponse HttpClient::recieve(long timeout) const{
    std::string response = read(timeout); ;
    
    HttpResponse http_response = HttpHeaderParser::parse_response(response);
    if(http_response.get_status() == Status::UNKNOWN){
        int retry_count = 3;
        while(retry_count && http_response.get_status() == Status::UNKNOWN){
            response.append(read(timeout));
            http_response = HttpHeaderParser::parse_response(response);
            --retry_count;
        }
    } 
    size_t content_len = http_response.content_len();
    
    if(content_len >= std::numeric_limits<unsigned int>::max()){
        throw std::runtime_error{"server response is too big!"};
    }
    
    size_t actual_content_len = http_response.data_len();
    while(content_len > actual_content_len){
        const std::string& data = read(timeout);
        actual_content_len += data.length();
        http_response.append_data(data);
    }
    
    return http_response;
}

std::string HttpClient::read(long timeout) const {
    std::string result{};

    if(socket->wait_for_read(timeout)){
        const static unsigned int buff_size = 1024;
        char buff[buff_size] = {};
       
        while(int count = socket->read(buff, buff_size)){
           if(count < 0){
                if(errno == EINTR){
                    continue;
                }else if(errno == EAGAIN || errno == EWOULDBLOCK){
                    break;
                }else{
                   std::string err_msg = "Failed to recieve data : ";
                   err_msg += gai_strerror(errno);
                   throw std::runtime_error(err_msg);
                }
            }
            result.append(buff, static_cast<size_t>(count));
            std::memset(buff, 0, buff_size);
        }
    }

    return result;
}

void HttpClient::connect(){
    disconnect();
    
    switch(protocol){
        case HttpProtocol::HTTPS:
            socket = new Socket::SSLSocket(host, "https");
            break;
        case HttpProtocol::HTTP:
            socket = new Socket::TCPSocket(host, "http");
            break;
    }
    socket->make_non_blocking();
}

void HttpClient::disconnect(){
     if(socket != nullptr){
        socket->close();
        delete socket;
        socket = nullptr;
    } 
}

}
