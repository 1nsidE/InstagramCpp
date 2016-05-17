#ifndef SSL_SERVICE_H
#define SSL_SERVICE_H

#include <string>
#include <openssl/ssl.h>

#include "TCPSocket.h"

namespace Socket{
    void init();
    
class SSLSocket : public TCPSocket{
public:
    SSLSocket(const std::string& hostname, const std::string& port);
    SSLSocket(const SSLSocket& ssl_sock) = delete;
    SSLSocket(SSLSocket&& ssl_sock);

    virtual ~SSLSocket();
    virtual SSLSocket& operator=(SSLSocket&& ssl_socket);

    virtual int write(const void *data, size_t len) const;
    virtual int read(void *buf, size_t len) const;
    virtual void close();
private:
    void  throw_error(const char* err_msg, unsigned long code) const;
    void connect();
    SSL* ssl = nullptr;
    SSL_CTX* ctx = nullptr;
};

}

#endif
