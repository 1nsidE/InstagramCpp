#include <stdexcept>
#include <gnutls/gnutls.h>
#include <gnutls/x509.h>

#include "SSLSocket.h"

namespace Socket {

    void at_exit_ssl();

    SSLSocket::SSLSocket(const std::string& hostname, const std::string& port) : TCPSocket{ hostname, port } {
        SSLSocket::init();
        SSLSocket::connect(hostname);
    }

    SSLSocket::SSLSocket(SSLSocket&& ssl_socket) : TCPSocket(std::forward<TCPSocket>(ssl_socket)), session{ std::move(ssl_socket.session) }, credentials{ std::move(ssl_socket.credentials) } {}

    SSLSocket::~SSLSocket() {
        SSLSocket::close();
    }

    SSLSocket &SSLSocket::operator=(SSLSocket &&ssl_socket) {
        if (this != &ssl_socket) {
            TCPSocket::operator=(std::forward<TCPSocket>(ssl_socket));

            session = std::move(ssl_socket.session);

            sockfd = ssl_socket.sockfd;
            ssl_socket.sockfd = -1;
        }
        return *this;
    }

    void SSLSocket::init() {
        static bool is_initialized = false; //TODO: make threadsafe
        if (!is_initialized) {
            int result = gnutls_global_init();
            
            if (result < 0) {
                throw_error(gnutls_strerror(result));
            }

            is_initialized = true;
        }
    }

    void SSLSocket::connect(const std::string& hostname) {
        int result{ 0 };

        check(result = gnutls_certificate_allocate_credentials(&credentials));
        check(gnutls_certificate_set_x509_system_trust(credentials));
        check(gnutls_init(&session, GNUTLS_CLIENT));
        check(gnutls_server_name_set(session, GNUTLS_NAME_DNS, hostname.c_str(), hostname.size()));
        check(gnutls_set_default_priority(session));
        check(gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE, credentials));

        gnutls_session_set_verify_cert(session, hostname.c_str(), 0);
        gnutls_transport_set_int(session, sockfd);
        gnutls_handshake_set_timeout(session, GNUTLS_DEFAULT_HANDSHAKE_TIMEOUT);

        do {
            result = gnutls_handshake(session);
        } while (result < 0 && gnutls_error_is_fatal(result) == 0);

        if (result < 0) {
            throw_error(gnutls_strerror(result));
        }
        std::atexit(at_exit_ssl);
    }

    inline void SSLSocket::check(int result) {
        if (result < 0) {
            throw_error(gnutls_strerror(result));
        }
    }

    long SSLSocket::write(const void *data, size_t len) {
        long count = gnutls_record_send(session, data, len);
        return count;
    }

    long SSLSocket::read(void *buf, size_t len) {
        long count = gnutls_record_recv(session, buf, len);
        return count;
    }

    void SSLSocket::close() {
        gnutls_bye(session, GNUTLS_SHUT_RDWR);
        TCPSocket::close();

        gnutls_deinit(session);
        gnutls_certificate_free_credentials(credentials);
    }

    void SSLSocket::throw_error(const char* err_msg) const {
        throw std::runtime_error(err_msg);
    }

    void at_exit_ssl() {
        gnutls_global_deinit();
    }
}

