//
// Created by inside on 4/23/16.
//

#ifndef FOLLOGRAPH_HTTPSOCKET_H
#define FOLLOGRAPH_HTTPSOCKET_H

#include "Http.h"
#include "HttpResponse.h"
#include "HttpRequest.h"
#include "TCPSocket.h"

#define STANDART_USER_AGENT "http_cpp"

namespace Http{

class HttpClient {
public:
    HttpClient(const std::string& _host, HttpProtocol _protocol);
    HttpClient(HttpClient&) = delete;
    HttpClient(HttpClient&& http_socket);
    ~HttpClient();
    
    HttpResponse get(const HttpUrl& url);
    HttpResponse post(const HttpUrl& url, const std::string& data, const std::string& content_type);
    HttpResponse post(const HttpUrl& url, const std::pair<std::string, std::string>& type_and_data);

    HttpResponse send_request(const HttpRequest& http_request);
	HttpResponse operator<<(const HttpRequest& http_request);
private:
    HttpRequest get_standart_request();
    void send(const HttpRequest& http_request);
    HttpResponse recieve(long timeout);

    std::string read(long timeout);
    std::string read_until(size_t len, long timeout);

    void connect();
    void disconnect();

    Socket::TCPSocket *socket;
    std::string host;
    HttpProtocol protocol;
    bool connected;
};

}

#endif //FOLLOGRAPH_HTTPSOCKET_H
