#ifndef SSL_SERVICE_H
#define SSL_SERVICE_H

#include <string>
#include <gnutls/gnutls.h>
#include "TCPSocket.h"

namespace Socket{

    class SSLSocket : public TCPSocket{
    public:
        SSLSocket(const std::string& hostname, const std::string& port);
        SSLSocket(const SSLSocket& ssl_sock) = delete;
        SSLSocket(SSLSocket&& ssl_sock);

        virtual ~SSLSocket();
        virtual SSLSocket& operator=(SSLSocket&& ssl_socket);

        long write(const void *data, size_t len) override;
        long read(void *buf, size_t len) override;

        void close() override;
    private:
        void init();
        [[noreturn]] void  throw_error(const char* err_msg) const;
        void connect(const std::string& hostname);
        void verify_hostname(const std::string& hostname);

        inline void check(int result);
        gnutls_session_t session{};
        gnutls_certificate_credentials_t credentials;
    };

}

#endif
