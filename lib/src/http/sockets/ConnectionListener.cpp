//
// Created by inside on 4/10/16.
//

#ifdef __linux__
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#ifdef WIN32
#include <Ws2tcpip.h>
#include <Winsock2.h>

#endif

#include <cstring>

#include "ConnectionListener.h"

namespace Socket {

    ConnectionListener::ConnectionListener(unsigned int _port) : port(_port) {
        init();
    }

    ConnectionListener::ConnectionListener(ConnectionListener &&connections_listener) : server_sockfd(connections_listener.server_sockfd), port(connections_listener.port) {
        connections_listener.server_sockfd = -1;
        connections_listener.port = 0;
    }

    ConnectionListener::~ConnectionListener() {
        close();
    }

    void ConnectionListener::init() {
        addrinfo* res;
        addrinfo hints;

        std::memset(&hints, 0, sizeof(hints));
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_family = AF_UNSPEC;
        hints.ai_flags = AI_PASSIVE;

        int status = getaddrinfo(nullptr, std::to_string(port).c_str(), &hints, &res);
        if (status != 0) {
            std::string err_msg = "getaddrinfo() failed : ";
            err_msg += gai_strerror(errno);
            throw std::runtime_error(err_msg);
        }

        for (addrinfo* tmp_addrinfo = res; tmp_addrinfo != nullptr; tmp_addrinfo = tmp_addrinfo->ai_next) {
            server_sockfd = socket(tmp_addrinfo->ai_family, tmp_addrinfo->ai_socktype, tmp_addrinfo->ai_protocol);
            if (server_sockfd == -1) {
                continue;
            }

            #ifdef __linux__
            int yes = 1;
            #endif

            #ifdef WIN32
            char yes = 1;
            #endif
            if (setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
                std::string err_msg = "failed to configure socket as reusable : ";
                err_msg += gai_strerror(errno);
                throw std::runtime_error(err_msg);
            }

            if (bind(server_sockfd, tmp_addrinfo->ai_addr, tmp_addrinfo->ai_addrlen) == -1) {
                ConnectionListener::close();

                std::string err_msg = "bind() failed : ";
                err_msg += gai_strerror(errno);
                throw std::runtime_error(err_msg);
            }

            break;
        }

        if (server_sockfd == -1) {
            throw std::runtime_error("failed to create socket");
        }
        freeaddrinfo(res);

        if (listen(server_sockfd, 256) == -1) { //TODO : make configurable
            std::string err_msg = "listen() failed :  ";
            err_msg += gai_strerror(errno);
            throw std::runtime_error(err_msg);
        }
    }

    TCPSocket ConnectionListener::wait() {
        return is_blocking ? blocking_wait() : nonblocking_wait();
    }

    TCPSocket ConnectionListener::blocking_wait() {
        sockaddr_storage client_sockaddr;

        socklen_t client_sockaddr_size = sizeof(client_sockaddr);
        int client_sockfd = accept(server_sockfd, reinterpret_cast<sockaddr*>(&client_sockaddr), &client_sockaddr_size);
        if (client_sockfd == -1) {
            //TODO : report about invalid client socket
        }

        return TCPSocket(client_sockfd, false);
    }

    TCPSocket ConnectionListener::nonblocking_wait() {
        throw std::runtime_error{ "Not implemented!" };
    }

    void ConnectionListener::close() {
        if (server_sockfd != -1) {
#ifdef __linux__
            ::close(server_sockfd);
#endif

#ifdef WIN32
            closesocket(server_sockfd);
#endif
        }
    }

#ifdef __linux__
    void ConnectionListener::make_non_blocking() {
        if (server_sockfd != -1) {
            int flags = fcntl(server_sockfd, F_GETFL, 0);
            if (flags < 0) {
                std::string err_msg = "failed to get socket flags : ";
                err_msg += gai_strerror(errno);
                throw std::runtime_error(err_msg);
            }
            flags |= O_NONBLOCK;
            if (fcntl(server_sockfd, F_SETFL, flags) < 0) {
                std::string err_msg = "failed to change socket to non-blocking mode : ";
                err_msg += gai_strerror(errno);
                throw std::runtime_error(err_msg);
            }
            is_blocking = true;
        }
        else {
            throw std::runtime_error("not connected!");
        }
    }
#endif

}
