#ifndef SSL_SERVICE_H
#define SSL_SERVICE_H

#include <string>

#include <gnutls/gnutls.h>
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
        [[noreturn]] void  throwError(const char* errMsg) const;
        void connect(const std::string& hostname);

        inline void check(int result);
        gnutls_session_t m_session{};
        gnutls_certificate_credentials_t m_credentials;
    };

}

#endif
