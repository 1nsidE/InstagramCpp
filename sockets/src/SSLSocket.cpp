#include <stdexcept>
#include <openssl/err.h>
#include <openssl/x509v3.h>
#include "SSLSocket.h"

namespace Socket {
    [[noreturn]] inline void throwSslError();

    class SSLInit{
    public:        
        SSLInit(){
            SSL_load_error_strings();
            SSL_library_init();
        }

        ~SSLInit(){

        }
    };

    static SSLInit sslInit{};

    SSLSocket::SSLSocket(const std::string& hostname, const std::string& port) : TCPSocket{hostname, port} {
        SSLSocket::connect(hostname);
    }

    SSLSocket::SSLSocket(SSLSocket&& sslSocket) : TCPSocket(std::move(sslSocket)), m_ssl{sslSocket.m_ssl}, m_ctx{sslSocket.m_ctx} {
        sslSocket.m_ctx = nullptr;
        sslSocket.m_ssl = nullptr;
    }
    

    SSLSocket::~SSLSocket() {
        SSLSocket::close();
    }

    SSLSocket &SSLSocket::operator=(SSLSocket &&sslSocket) {
        if (this != &sslSocket) {
            TCPSocket::operator=(std::move(sslSocket));
            m_ssl = sslSocket.m_ssl;
            m_ctx = sslSocket.m_ctx;

            sslSocket.m_ssl = nullptr;
            sslSocket.m_ctx = nullptr;
        }
        return *this;
    }

    void SSLSocket::connect(const std::string& hostname) {
        m_ctx = SSL_CTX_new(SSLv23_client_method());
        m_ssl = SSL_new(m_ctx);

        if(m_ssl == nullptr){
            throwSslError();
        }

        if(!SSL_set_fd(m_ssl, m_sockfd)){
            throwSslError();
        }

        if(SSL_connect(m_ssl) != 1){
            throwSslError();
        }
    }

    long SSLSocket::write(const void *data, size_t len) {
        long count = SSL_write(m_ssl, data, static_cast<int>(len));
        return count;
    }

    long SSLSocket::read(void *buf, size_t len) {
        long count = SSL_read(m_ssl, buf, static_cast<int>(len));
        return count;
    }

    void SSLSocket::close() {
        SSL_free(m_ssl);
        SSL_CTX_free(m_ctx);
        TCPSocket::close();
    }

    [[noreturn]] inline void throwSslError() {
        throw std::runtime_error(ERR_lib_error_string(ERR_peek_last_error()));
    }


}
