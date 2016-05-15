//
// Created by inside on 4/23/16.
//

#ifndef FOLLOGRAPH_HTTPSOCKET_H
#define FOLLOGRAPH_HTTPSOCKET_H

#include "Http.h"
#include "HttpResponse.h"
#include "HttpRequest.h"
#include "TCPSocket.h"

namespace Http{

class HttpClient {
public:
    HttpClient(const std::string& _host, HttpProtocol _protocol);
    HttpClient(HttpClient&) = delete;
    HttpClient(HttpClient&& http_socket);
    ~HttpClient();

    HttpResponse send_request(const HttpRequest& http_request);
	HttpResponse operator<<(const HttpRequest& http_request);
private:
    void send(const HttpRequest& http_request) const;
    HttpResponse recieve(long timeout) const;

    std::string read(long timeout) const;
    std::string read_until(size_t len, long timeout) const;

    void connect();
    void disconnect();

    Socket::TCPSocket *socket;
    std::string host;
    HttpProtocol protocol;
};

}

#endif //FOLLOGRAPH_HTTPSOCKET_H
