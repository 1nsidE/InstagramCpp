//
// Created by inside on 4/23/16.
//

#include <Ws2tcpip.h>
#include <Winsock2.h>

#include <stdexcept>
#include <cstring>

#include "TCPSocket.h"

namespace Socket {

void atExit() {
    WSACleanup();
}

int init_wsa() {
    static bool is_wsa_initialized = false;
    int result = 0;
    if (!is_wsa_initialized) {
        WSAData data{};

        int result = WSAStartup(MAKEWORD(2, 2), &data);
        if (result != 0) {
            return result;
        }

        std::atexit(atExit);
        is_wsa_initialized = true;
    }
    return result;
}

std::string errorString(int code){
    char* msg = nullptr;

    if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, code, 0, &msg, 0, nullptr) == 0) {
        return "Unknown Error";
    }

    return msg;
}

TCPSocket::TCPSocket(const std::string &host, const std::string &port) {
   connect(host, port);
}

TCPSocket::TCPSocket(int sockfd, bool isBlocking) : m_sockfd{ sockfd }, m_isBlocking{ isBlocking } {}

TCPSocket::TCPSocket(TCPSocket&& tcpSocket) : m_sockfd{ tcpSocket.m_sockfd }, m_isBlocking{ tcpSocket.m_isBlocking } {
    tcpSocket.m_sockfd = -1;
    tcpSocket.m_isBlocking = false;
}

TCPSocket::~TCPSocket() {
    TCPSocket::close();
}

TCPSocket &TCPSocket::operator=(TCPSocket &&tcp_socket) {
    if (this != &tcp_socket) {
        m_sockfd = tcp_socket.m_sockfd;
        m_isBlocking = tcp_socket.m_isBlocking;

        tcp_socket.m_sockfd = -1;
        tcp_socket.m_isBlocking = false;
    }
    return *this;
}

void TCPSocket::connect(const std::string& host, const std::string& port) {
    addrinfo hints;
    addrinfo* res;
    std::memset(&hints, 0, sizeof(hints));

    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;

    if (getaddrinfo(host.c_str(), port.c_str(), &hints, &res) != 0) {
        if (WSAGetLastError() == WSANOTINITIALISED) {
            int result = init_wsa();
            if (!result) {
                throwError("Failed to initialize WSA : ", result);
            }
        }
        
        if(getaddrinfo(host.c_str(), port.c_str(), &hints, &res) != 0){
            throwError("getaddrinfo() failed: ", lastErrorCode());
        }
    }

    for (addrinfo* tmp_res = res; tmp_res != nullptr; tmp_res = res->ai_next) {
        m_sockfd = socket(tmp_res->ai_family, tmp_res->ai_socktype, tmp_res->ai_protocol);

        if (m_sockfd == -1) {
            continue;
        }

        if (::connect(m_sockfd, tmp_res->ai_addr, tmp_res->ai_addrlen) == -1) {
            throwError("connect() failed: ", lastErrorCode());
        }

        break;
    }

    if (m_sockfd == -1) {
        throwError("failed to craete socket : ", lastErrorCode());
    }

    freeaddrinfo(res);
}

long TCPSocket::write(const void *data, size_t length) {
    if (m_sockfd == -1) {
        throw std::runtime_error("not connected");
    }

    long count = send(m_sockfd, static_cast<const char*>(data), length, 0);
    return count;
}

long TCPSocket::read(void *data, size_t length) {
    if (m_sockfd == -1) {
        throw std::runtime_error("not_connected");
    }

    long count = recv(m_sockfd, static_cast<char*>(data), length, 0);

    return count;
}

void TCPSocket::close() {
    if (m_sockfd != -1) {
        closesocket(m_sockfd);
    }
}

std::string TCPSocket::getIp() const {
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
        unsigned long yes{ 1 };
        ioctlsocket(m_sockfd, FIONBIO, &yes);
        m_isBlocking = false;
    }
    else {
        throw std::runtime_error("not connected!");
    }
}

bool TCPSocket::waitForRead(unsigned int timeout) const {
    fd_set readfs{};
    readfs.fd_count = 1;
    readfs.fd_array[0] = m_sockfd;

    timeval time{};
    time.tv_sec = timeout * 1000;
    time.tv_usec = 0;

    int result = select(0, &readfs, nullptr, nullptr, &time);

    return result == SOCKET_ERROR ? false : result;
}

bool TCPSocket::waitForWrite(unsigned int timeout) const {
    fd_set writefs{};
    writefs.fd_count = 1;
    writefs.fd_array[0] = m_sockfd;

    timeval time{};
    time.tv_sec = timeout * 1000;
    time.tv_usec = 0;

    int result = select(0, &writefs, nullptr, nullptr, &time);

    return result == SOCKET_ERROR ? false : result;
}

Error TCPSocket::lastError() const {
    int code = lastErrorCode();
    switch (code) {
    case WSAEWOULDBLOCK:
        return Error::WOULDBLOCK;
    case WSAEINTR:
        return Error::INTERRUPTED;
    default:
        return Error::UNKNOWN;

    }
}

std::string TCPSocket::lastErrorString() const {
    int code = lastErrorCode();
    return errorString(code);
}

int TCPSocket::lastErrorCode() const {
    return WSAGetLastError();
}

void TCPSocket::throwError(const char* err_msg, int code) const {
    std::string msg{ err_msg };
    msg += errorString(code);
    throw std::runtime_error(err_msg);
}

}

