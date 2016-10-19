//
// Created by inside on 4/23/16.
//

#ifdef __linux__
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <poll.h>
#include <fcntl.h>
#endif

#ifdef WIN32
#include <Ws2tcpip.h>
#include <Winsock2.h>
#endif

#include <stdexcept>
#include <cstring>

#include "TCPSocket.h"

namespace Socket {

#ifdef WIN32
    void at_exit();
#endif

TCPSocket::TCPSocket(const std::string &host, const std::string &port) {
   connect(host, port);
}

TCPSocket::TCPSocket(int _sockfd, bool is_blocking_) : sockfd{ _sockfd }, is_blocking{ is_blocking_ } {}

TCPSocket::TCPSocket(TCPSocket&& client_socket) : sockfd{ client_socket.sockfd }, is_blocking{ client_socket.is_blocking } {
    client_socket.sockfd = -1;
    client_socket.is_blocking = false;
}

TCPSocket::~TCPSocket() {
    TCPSocket::close();
}

TCPSocket &TCPSocket::operator=(TCPSocket &&tcp_socket) {
    if (this != &tcp_socket) {
        sockfd = tcp_socket.sockfd;
        is_blocking = tcp_socket.is_blocking;

        tcp_socket.sockfd = -1;
        tcp_socket.is_blocking = false;
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
        #ifdef WIN32
        if (WSAGetLastError() == WSANOTINITIALISED) {
            init_wsa();
        }
        
        if(getaddrinfo(host.c_str(), port.c_str(), &hints, &res) != 0){
            throw_error("getaddrinfo() failed: ", last_err_code());
        }

        #endif

        #ifdef __linux__
        throw_error("getaddrinfo() failed: ", last_err_code());
        #endif
    }

    for (addrinfo* tmp_res = res; tmp_res != nullptr; tmp_res = res->ai_next) {
        sockfd = socket(tmp_res->ai_family, tmp_res->ai_socktype, tmp_res->ai_protocol);

        if (sockfd == -1) {
            continue;
        }

        if (::connect(sockfd, tmp_res->ai_addr, tmp_res->ai_addrlen) == -1) {
            throw_error("connect() failed: ", last_err_code());
        }

        break;
    }

    if (sockfd == -1) {
        throw_error("failed to craete socket : ", last_err_code());
    }

    freeaddrinfo(res);
}

long TCPSocket::write(const void *data, size_t length) {
    if (sockfd == -1) {
        throw std::runtime_error("not connected");
    }

    #ifdef __linux__
    long count = send(sockfd, data, length, 0);
    #endif

    #ifdef WIN32
    long count = send(sockfd, static_cast<const char*>(data), length, 0);
    #endif

    return count;
}

long TCPSocket::read(void *data, size_t length) {
    if (sockfd == -1) {
        throw std::runtime_error("not_connected");
    }

    #ifdef __linux__
    long count = recv(sockfd, data, length, 0);
    #endif

    #ifdef WIN32
    long count = recv(sockfd, static_cast<char*>(data), length, 0);
    #endif

    return count;
}

void TCPSocket::close() {
    if (sockfd != -1) {
        #ifdef __linux__
        ::close(sockfd);
        #endif

        #ifdef WIN32
        closesocket(sockfd);
        #endif
    }
}

std::string TCPSocket::get_ip() const {
    if (sockfd == -1) {
        return "";
    }

    struct sockaddr_storage addr;
    socklen_t addr_size = sizeof(sockaddr_storage);
    int len = getpeername(sockfd, reinterpret_cast<sockaddr*>(&addr), &addr_size);

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

#ifdef __linux__
void TCPSocket::make_non_blocking() {
    if (!is_blocking) {
        return;
    }

    if (sockfd != -1) {
        int flags = fcntl(sockfd, F_GETFL, 0);
        if (flags < 0) {
            throw_error("failed to get socket flags : ", last_err_code());
        }

        flags |= O_NONBLOCK;
        if (fcntl(sockfd, F_SETFL, flags) < 0) {
            throw_error("failed to change socket to non-blocking mode : ", last_err_code());
        }

        is_blocking = false;
    }
    else {
        throw std::runtime_error("not connected!");
    }
}

bool TCPSocket::wait_for_read(unsigned int timeout) const {
    pollfd pfd;

    pfd.fd = sockfd;
    pfd.events = POLLIN;
    int result = poll(&pfd, 1, 1000 * timeout);

    return result + 1;;
}

bool TCPSocket::wait_for_write(unsigned int timeout) const {
    pollfd pfd;

    pfd.fd = sockfd;
    pfd.events = POLLOUT;

    int result = poll(&pfd, 1, 1000 * timeout);
    return result + 1;

}

Error TCPSocket::get_last_err() const {
    switch (last_err_code()) {
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

std::string TCPSocket::get_last_err_str() const {
    return gai_strerror(last_err_code());
}

int TCPSocket::last_err_code() const {
    return errno;
}
#endif

#ifdef WIN32
void TCPSocket::init_wsa() {
    static bool is_wsa_initialized = false;  //TODO: make thread safe
    if (!is_wsa_initialized) {
        WSAData data{};

        int result = WSAStartup(MAKEWORD(2, 2), &data);
        if (result != 0) {
            throw_error("Failed to initalize WSA : ", result);
        }

        std::atexit(at_exit);
        is_wsa_initialized = true;
    }
}

void TCPSocket::make_non_blocking() {
    if (!is_blocking) {
        return;
    }

    if (sockfd != -1) {
        unsigned long yes{ 1 };
        ioctlsocket(sockfd, FIONBIO, &yes);
        is_blocking = false;
    }
    else {
        throw std::runtime_error("not connected!");
    }
}

bool TCPSocket::wait_for_read(long timeout) const {
    fd_set readfs{};
    readfs.fd_count = 1;
    readfs.fd_array[0] = sockfd;

    timeval time{};
    time.tv_sec = timeout * 1000;
    time.tv_usec = 0;

    int result = select(0, &readfs, nullptr, nullptr, &time);

    return result == SOCKET_ERROR ? false : result;
}

bool TCPSocket::wait_for_write(long timeout) const {
    fd_set writefs{};
    writefs.fd_count = 1;
    writefs.fd_array[0] = sockfd;

    timeval time{};
    time.tv_sec = timeout * 1000;
    time.tv_usec = 0;

    int result = select(0, &writefs, nullptr, nullptr, &time);

    return result == SOCKET_ERROR ? false : result;
}

Error TCPSocket::get_last_err() const {
    int code = WSAGetLastError();
    switch (code) {
    case WSAEWOULDBLOCK:
        return Error::WOULDBLOCK;
    case WSAEINTR:
        return Error::INTERRUPTED;
    default:
        return Error::UNKNOWN;

    }
}

std::string TCPSocket::get_last_err_str() const {
    int code = WSAGetLastError();
    char* msg = nullptr;

    if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, code, 0, msg, 0, nullptr) == 0) {
        return "Unknown Error";
    }

    return msg;
}

int TCPSocket::last_err_code() const {
    return WSAGetLastError();
}

void at_exit() {
    WSACleanup();
}
#endif

void TCPSocket::throw_error(const char* err_msg, int code) const {
    std::string msg{ err_msg };
    msg += get_last_err_str();
    throw std::runtime_error(err_msg);
}

}
