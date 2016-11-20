#include <stdexcept>
#include <gnutls/gnutls.h>
#include <gnutls/x509.h>

#include "SSLSocket.h"

namespace Socket {

    void atExitSsl();

    SSLSocket::SSLSocket(const std::string& hostname, const std::string& port) : TCPSocket{hostname, port} {
        SSLSocket::init();
        SSLSocket::connect(hostname);
    }

    SSLSocket::SSLSocket(SSLSocket&& sslSocket) : TCPSocket(std::forward<TCPSocket>(sslSocket)), 
                                                    m_session{std::move(sslSocket.m_session)}, 
                                                    m_credentials{std::move(sslSocket.m_credentials)} {}
    

    SSLSocket::~SSLSocket() {
        SSLSocket::close();
    }

    SSLSocket &SSLSocket::operator=(SSLSocket &&sslSocket) {
        if (this != &sslSocket) {
            TCPSocket::operator=(std::forward<TCPSocket>(sslSocket));

            m_session = std::move(sslSocket.m_session);

            m_sockfd = sslSocket.m_sockfd;
            sslSocket.m_sockfd = -1;
        }
        return *this;
    }

    void SSLSocket::init() {
        static bool is_initialized = false; //TODO: make threadsafe
        if (!is_initialized) {
            int result = gnutls_global_init();
            
            if (result < 0) {
                throwError(gnutls_strerror(result));
            }

            std::atexit(atExitSsl);
            is_initialized = true;
        }
    }

    void SSLSocket::connect(const std::string& hostname) {
        int result{ 0 };

        check(result = gnutls_certificate_allocate_credentials(&m_credentials));
        check(gnutls_certificate_set_x509_system_trust(m_credentials));
        check(gnutls_init(&m_session, GNUTLS_CLIENT));
        check(gnutls_server_name_set(m_session, GNUTLS_NAME_DNS, hostname.c_str(), hostname.size()));
        check(gnutls_set_default_priority(m_session));
        check(gnutls_credentials_set(m_session, GNUTLS_CRD_CERTIFICATE, m_credentials));

        gnutls_session_set_verify_cert(m_session, hostname.c_str(), 0);
        gnutls_transport_set_int(m_session, m_sockfd);
        gnutls_handshake_set_timeout(m_session, GNUTLS_DEFAULT_HANDSHAKE_TIMEOUT);

        do {
            result = gnutls_handshake(m_session);
        } while (result < 0 && gnutls_error_is_fatal(result) == 0);

        if (result < 0) {
            throwError(gnutls_strerror(result));
        }

    }

    inline void SSLSocket::check(int result) {
        if (result < 0) {
            throwError(gnutls_strerror(result));
        }
    }

    long SSLSocket::write(const void *data, size_t len) {
        long count = gnutls_record_send(m_session, data, len);
        return count;
    }

    long SSLSocket::read(void *buf, size_t len) {
        long count = gnutls_record_recv(m_session, buf, len);
        return count;
    }

    void SSLSocket::close() {
        gnutls_bye(m_session, GNUTLS_SHUT_RDWR);
        TCPSocket::close();

        gnutls_deinit(m_session);
        gnutls_certificate_free_credentials(m_credentials);
    }

    void SSLSocket::throwError(const char* err_msg) const {
        throw std::runtime_error(err_msg);
    }

    void atExitSsl() {
        gnutls_global_deinit();
    }
}

