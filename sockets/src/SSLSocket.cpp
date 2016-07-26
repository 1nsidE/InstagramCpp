#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <cstring>
#include <stdexcept>
#include <utility>

#include <openssl/err.h>
#include <openssl/x509v3.h>

#include "SSLSocket.h"
namespace Socket{

    SSLSocket::SSLSocket(const std::string& hostname, const std::string& port) : TCPSocket{hostname, port}, ssl{nullptr}, ctx{nullptr}{
        init();
        connect(hostname);
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
            TCPSocket::operator=(std::forward<TCPSocket>(ssl_socket));

            ssl = ssl_socket.ssl;
            ssl_socket.ssl = nullptr;

            ctx = ssl_socket.ctx;
            ssl_socket.ctx = nullptr;

            sockfd = ssl_socket.sockfd;
            ssl_socket.sockfd = -1;
        }
        return *this;
    }

    void SSLSocket::init(){
        static bool is_initialized = false;
        if(!is_initialized){
            SSL_library_init();
            SSL_load_error_strings();
            OpenSSL_add_ssl_algorithms();
            ERR_load_CRYPTO_strings();

            is_initialized = true;
        }
    }
    
    void SSLSocket::connect(const std::string& hostname){
        const SSL_METHOD* method = TLSv1_2_method();
        if(method == nullptr){
            throw_error("failed to get SSL method! : ", ERR_get_error());
        }

        ctx = SSL_CTX_new(method);
        if(ctx == nullptr){
            throw_error("failed to get SSL context : ", ERR_get_error());
        }

        ssl = SSL_new(ctx);
        if(ssl == nullptr){
            throw_error("failed to get SSL object : ", ERR_get_error());
        }

        X509_VERIFY_PARAM* param = SSL_get0_param(ssl);
        /* Enable automatic hostname checks */
        X509_VERIFY_PARAM_set_hostflags(param, X509_CHECK_FLAG_NO_PARTIAL_WILDCARDS);
        X509_VERIFY_PARAM_set1_host(param, hostname.c_str(), hostname.size());
        //TODO : make configrable
        SSL_set_verify(ssl, SSL_VERIFY_NONE, nullptr);

        SSL_set_fd(ssl, sockfd);
        if(SSL_connect(ssl) < 0){
            throw_error("failed to establish secure connection : ", ERR_get_error());
        }
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
            ctx = nullptr;
        }

        if(ssl != nullptr){
            SSL_shutdown(ssl);
            SSL_free(ssl);
            ssl = nullptr;
        }
    }

    void SSLSocket::throw_error(const char* err_msg, unsigned long code) const {
        if(code == 0){
            throw std::runtime_error(err_msg);
        }else{
            const static unsigned int err_msg_size = 512;
            std::string msg{err_msg};
            char buff[err_msg_size] = {0};
            ERR_error_string_n(code, buff, err_msg_size);

            msg += buff;
            throw std::runtime_error(msg);
        }
    }

}

