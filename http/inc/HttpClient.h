//
// Created by inside on 4/23/16.
//

#ifndef FOLLOGRAPH_HTTPSOCKET_H
#define FOLLOGRAPH_HTTPSOCKET_H

#include <memory>
#include <unordered_map>

#include "Http.h"

namespace Socket{
    class TCPSocket;
}

namespace Http {

class FormData;
class HttpRequest;
class HttpResponse;
class HttpUrl;

class EXPORT_HTTP HttpClient {
public:
    HttpClient();
    HttpClient(HttpClient&) = delete;
    HttpClient(HttpClient&& http_socket);
    ~HttpClient();

    HttpClient& operator=(HttpClient&& client);

    HttpResponse get(const HttpUrl& url);
    HttpResponse post(const HttpUrl& url, const std::string& data, const std::string& contentType);
    HttpResponse post(const HttpUrl& url, const std::pair<std::string, std::string>& typeAndData);
    HttpResponse post(const HttpUrl& url, const FormData& form_data);
    HttpResponse del(const HttpUrl& url);

    HttpResponse sendRequest(const HttpRequest& httpRequest);
    HttpResponse operator<<(const HttpRequest& httpRequest);
    HttpResponse operator<<(const HttpUrl& url);

private:
    HttpRequest getDefaultRequest() const;
    void send(const HttpRequest& httpRequest);

    HttpResponse receive(const HttpUrl& url, unsigned int timeout);
    std::string read(const HttpUrl& url, unsigned int timeout);
    std::string read_until(size_t len, long timeout);

    using SocketPtr = std::shared_ptr<Socket::TCPSocket>;
    SocketPtr getSocket(const HttpUrl& url);
    SocketPtr connect(const HttpUrl& url);
    void disconnect(const HttpUrl& url);

    using HostToSocketMap = std::unordered_map<std::string, SocketPtr>;
    HostToSocketMap m_hostToSocketMap{};

    EXPORT_HTTP friend void swap(HttpClient& first, HttpClient& second);
};

}

#endif //FOLLOGRAPH_HTTPSOCKET_H
