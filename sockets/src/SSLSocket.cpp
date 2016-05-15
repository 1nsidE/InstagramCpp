#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <cstring>
#include <stdexcept>
#include <utility>
#include <openssl/err.h>
#include "SSLSocket.h"

namespace Socket{
    
    void init(){
        SSL_library_init();
        SSL_load_error_strings();

        OpenSSL_add_ssl_algorithms();
        ERR_load_CRYPTO_strings();
    }
    
    SSLSocket::SSLSocket(const std::string& hostname, const std::string& port) : TCPSocket{hostname, port}, ssl{nullptr}, ctx{nullptr}{
        const SSL_METHOD* method = TLSv1_2_client_method();
        ctx = SSL_CTX_new(method);
        if(ctx == nullptr){
            init();
            ctx = SSL_CTX_new(method);
        }
        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, sockfd);
        SSL_connect(ssl);
    }

    SSLSocket::SSLSocket(SSLSocket&& ssl_socket) : TCPSocket(std::forward<TCPSocket>(ssl_socket)), ssl(ssl_socket.ssl), ctx(ssl_socket.ctx){
        ssl_socket.ssl = nullptr;
        ssl_socket.ctx = nullptr;
    }

    SSLSocket::~SSLSocket(){
        close();
    }

    SSLSocket &SSLSocket::operator=(SSLSocket &&ssl_socket) {
        if(this != &ssl_socket){
            ssl = ssl_socket.ssl;
            ssl_socket.ssl = nullptr;

            ctx = ssl_socket.ctx;
            ssl_socket.ctx = nullptr;

            sockfd = ssl_socket.sockfd;
            ssl_socket.sockfd = -1;
        }
        return *this;
    }

    int SSLSocket::write(const void *data, size_t len) const{
        int count = SSL_write(ssl, data, len);
        return count;
    }

    int SSLSocket::read(void *buf, size_t len) const{
        int count = SSL_read(ssl, buf, len);
        return count;
    }

    void SSLSocket::close() {
        if(ctx != nullptr){
            SSL_CTX_free(ctx);
        }

        TCPSocket::close();
    }

    void SSLSocket::throw_error(const char* err_msg, unsigned long code) const {
        const static unsigned int err_msg_size = 512;
        std::string msg{err_msg};
        char buff[err_msg_size] = {0};
        ERR_error_string_n(code, buff, err_msg_size);
        
        msg += buff;
        throw std::runtime_error(msg);
    }
}
