//
// Created by inside on 4/23/16.
//

#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include "TCPSocket.h"

namespace Socket{

TCPSocket::TCPSocket(const std::string &host, const std::string &port) {
    connect(host, port);
}

TCPSocket::TCPSocket(int _sockfd) : sockfd{_sockfd} {
    sockfd = _sockfd;
}

TCPSocket::TCPSocket(TCPSocket&& client_socket) : sockfd{client_socket.sockfd}, is_blocking{client_socket.is_blocking}{
    client_socket.sockfd = -1;
    client_socket.is_blocking = false;
}

TCPSocket::~TCPSocket(){
    if(sockfd != -1){
        ::close(sockfd);
    }
}

TCPSocket &TCPSocket::operator=(TCPSocket &&tcp_socket) {
    if(this != &tcp_socket){
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

    if(getaddrinfo(host.c_str(), port.c_str(), &hints, &res) == -1){
        throw_error("getaddrinfo() failed: ", errno);
    }
    
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(sockfd == -1){
        throw_error("failed to create socket: ", errno);
    }

    if(::connect(sockfd, res->ai_addr, res->ai_addrlen) == -1){
        throw_error("connect() failed: ", errno);
    }
    
    freeaddrinfo(res);
}

int TCPSocket::write(const void *data, size_t length) const {
    if(sockfd == -1){
        throw std::runtime_error("not connected");
    }

    int count = send(sockfd, data, length, 0);
    return count;
}

int TCPSocket::read(void *data, size_t length) const {
    if (sockfd == -1) {
        throw std::runtime_error("not_connected");
    }

    int count = recv(sockfd, data, length, 0);
    return count;
}

void TCPSocket::close(){
    if(sockfd != -1){
        ::close(sockfd);
    }
}

std::string TCPSocket::get_ip() const {
    if(sockfd == -1){
        return "";
    }

    struct sockaddr_storage addr;
    socklen_t addr_size = sizeof(sockaddr_storage);
    int len = getpeername(sockfd, reinterpret_cast<sockaddr*>(&addr), &addr_size);

    if(len != -1) {
        if (addr.ss_family == AF_INET) {
            char ip[INET_ADDRSTRLEN];
            sockaddr_in *in = reinterpret_cast<sockaddr_in *>(&addr);
            if(inet_ntop(AF_INET, &in->sin_addr, ip, INET_ADDRSTRLEN)){
                return ip;
            }
        } else if (addr.ss_family == AF_INET6) {
            char ip[INET6_ADDRSTRLEN];
            sockaddr_in6 *in6 = reinterpret_cast<sockaddr_in6 *>(&addr);
            if(inet_ntop(AF_INET6, &in6->sin6_addr, ip, INET6_ADDRSTRLEN)){
                return ip;
            }
        }
    }

    return "Invalid";
}

void TCPSocket::make_non_blocking(){
    if(sockfd != -1){
        int flags = fcntl(sockfd, F_GETFL, 0);
        if(flags < 0){
            throw_error("failed to get socket flags : ", errno);
        }
        flags |= O_NONBLOCK;
        if(fcntl(sockfd, F_SETFL, flags) < 0){
            throw_error("failed to change socket to non-blocking mode : ", errno);
        }
        is_blocking = true;
    }else{
        throw std::runtime_error("not connected!");
    }
}
bool TCPSocket::wait_for_read(long timeout) const{
    pollfd pfd;
   
    pfd.fd = sockfd;
    pfd.events = POLLIN;
    int result = poll(&pfd, 1, 1000*timeout);

    return result + 1;;
}

bool TCPSocket::wait_for_write(long timeout) const{
    throw std::runtime_error{"Not Implemented"};
}

void TCPSocket::throw_error(const char* err_msg, int code) const{
    std::string msg{err_msg};
    msg += gai_strerror(code);
    throw std::runtime_error(err_msg);
}

}
