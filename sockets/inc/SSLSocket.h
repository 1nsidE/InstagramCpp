#ifndef SSL_SERVICE_H
#define SSL_SERVICE_H

#include <string>

#include <openssl/ssl.h>
#include "TCPSocket.h"

namespace Socket{

    class SSLSocket : public TCPSocket{
    public:
        SSLSocket(const std::string& hostname, const std::string& port);
        SSLSocket(const SSLSocket& sslSocket) = delete;
        SSLSocket(SSLSocket&& sslSocket);

        virtual ~SSLSocket();
        virtual SSLSocket& operator=(SSLSocket&& sslSocket);

        long write(const void *data, size_t len) override;
        long read(void *buf, size_t len) override;

        void close() override;
    private:
        void init();
        void connect();

        SSL* m_ssl;
        SSL_CTX* m_ctx;
        std::string m_hostname{};
    };
}

#endif
