//
// Created by inside on 4/23/16.
//

#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <poll.h>
#include <fcntl.h>

#include <stdexcept>
#include <cstring>

#include "TCPSocket.h"

namespace Socket {

void throwError(const char* errMsg, int code);

void TCPSocket::connect(const std::string& host, const std::string& port) {
    addrinfo hints;
    addrinfo* res;
    std::memset(&hints, 0, sizeof(hints));

    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;

    if (getaddrinfo(host.c_str(), port.c_str(), &hints, &res) != 0) {
        throwError("getaddrinfo() failed", lastErrorCode());
    }

    for (addrinfo* tmp_res = res; tmp_res != nullptr; tmp_res = res->ai_next) {
        m_sockfd = socket(tmp_res->ai_family, tmp_res->ai_socktype, tmp_res->ai_protocol);

        if (m_sockfd == -1) {
            continue;
        }

        if (::connect(m_sockfd, tmp_res->ai_addr, tmp_res->ai_addrlen) == -1) {
            close();
        }

        break;
    }

    freeaddrinfo(res);

    if (m_sockfd == -1) {
        throwError("failed to create socket", lastErrorCode());
    }
}

long TCPSocket::write(const void *data, size_t length) {
    if (m_sockfd == -1) {
        throw std::runtime_error("not connected");
    }

    long count = send(m_sockfd, data, length, 0);

    return count;
}

long TCPSocket::read(void *data, size_t length) {
    if (m_sockfd == -1) {
        throw std::runtime_error("not_connected");
    }

    long count = recv(m_sockfd, data, length, 0);

    return count;
}

void TCPSocket::close() {
    if (m_sockfd != -1) {
        ::close(m_sockfd);
        m_sockfd = -1;
    }
}

std::string TCPSocket::ip() const {
    if (m_sockfd == -1) {
        return "";
    }

    struct sockaddr_storage addr;
    socklen_t addr_size = sizeof(sockaddr_storage);
    int len = getpeername(m_sockfd, reinterpret_cast<sockaddr*>(&addr), &addr_size);

    if (len != -1) {
        if (addr.ss_family == AF_INET) {
            char ip[INET_ADDRSTRLEN];
            sockaddr_in *in = reinterpret_cast<sockaddr_in *>(&addr);
            if (inet_ntop(AF_INET, &in->sin_addr, ip, INET_ADDRSTRLEN)) {
                return ip;
            }
        }
        else if (addr.ss_family == AF_INET6) {
            char ip[INET6_ADDRSTRLEN];
            sockaddr_in6 *in6 = reinterpret_cast<sockaddr_in6 *>(&addr);
            if (inet_ntop(AF_INET6, &in6->sin6_addr, ip, INET6_ADDRSTRLEN)) {
                return ip;
            }
        }
    }

    return "Invalid";
}

void TCPSocket::makeNonBlocking() {
    if (!m_isBlocking) {
        return;
    }

    if (m_sockfd != -1) {
        int flags = fcntl(m_sockfd, F_GETFL, 0);
        if (flags < 0) {
            throwError("failed to get socket flags", lastErrorCode());
        }

        flags |= O_NONBLOCK;
        if (fcntl(m_sockfd, F_SETFL, flags) < 0) {
            throwError("failed to change socket to non-blocking mode", lastErrorCode());
        }

        m_isBlocking = false;
    }
    else {
        throw std::runtime_error("not connected!");
    }
}

bool TCPSocket::waitForRead(unsigned int timeout) const {
    pollfd pfd;

    pfd.fd = m_sockfd;
    pfd.events = POLLIN;
    int result = poll(&pfd, 1, 1000 * timeout);

    return result + 1;;
}

bool TCPSocket::waitForWrite(unsigned int timeout) const {
    pollfd pfd;

    pfd.fd = m_sockfd;
    pfd.events = POLLOUT;

    int result = poll(&pfd, 1, 1000 * timeout);
    return result + 1;

}

Error TCPSocket::lastError() const {
    switch (lastErrorCode()) {
    case EWOULDBLOCK:
        return Error::WOULDBLOCK;
    case EINTR:
        return Error::INTERRUPTED;
    case EPIPE:
        return Error::PIPE_BROKEN;
    default:
        return Error::UNKNOWN;

    }
}

std::string TCPSocket::lastErrorString() const {
    return gai_strerror(lastErrorCode());
}

int TCPSocket::lastErrorCode() const {
    return errno;
}

void throwError(const char* errMsg, int code) {
    std::string msg{errMsg};
    msg =  msg + " : " + gai_strerror(code);
    throw std::runtime_error(msg);
}

}
