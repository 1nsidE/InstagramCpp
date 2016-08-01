//
// Created by inside on 4/23/16.
//

#ifdef __linux__
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <poll.h>
#endif

#ifdef WIN32
#include <Ws2tcpip.h>
#include <Winsock2.h>
#endif

#include <stdexcept>
#include <cstring>
#include <fcntl.h>

#include "TCPSocket.h"

namespace Socket{

	TCPSocket::TCPSocket(const std::string &host, const std::string &port) {
        connect(host, port);
    }

	TCPSocket::TCPSocket(int _sockfd, bool is_blocking_) : sockfd{_sockfd}, is_blocking{is_blocking_} {}

    TCPSocket::TCPSocket(TCPSocket&& client_socket) : sockfd{client_socket.sockfd}, is_blocking{client_socket.is_blocking}{
        client_socket.sockfd = -1;
        client_socket.is_blocking = false;
    }

    TCPSocket::~TCPSocket(){
		TCPSocket::close();
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

		WSAData data{};
		WSAStartup(MAKEWORD(2, 2), &data);

        hints.ai_socktype = SOCK_STREAM;
        hints.ai_family = AF_UNSPEC;

        if(getaddrinfo(host.c_str(), port.c_str(), &hints, &res) != 0){
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

    long TCPSocket::write(const void *data, size_t length) {
        if(sockfd == -1){
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

    void TCPSocket::close(){
        if(sockfd != -1){
			#ifdef __linux__
			::close(sockfd);
			#endif

			#ifdef WIN32
			closesocket(sockfd);
			#endif
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

#ifdef __linux__
    void TCPSocket::make_non_blocking(){
		if (!is_blocking) {
			return;
		}

		if(sockfd != -1){
            int flags = fcntl(sockfd, F_GETFL, 0);
            if(flags < 0){
                throw_error("failed to get socket flags : ", errno);
            }

            flags |= O_NONBLOCK;
            if(fcntl(sockfd, F_SETFL, flags) < 0){
                throw_error("failed to change socket to non-blocking mode : ", errno);
            }

            is_blocking = false;
        }else{
            throw std::runtime_error("not connected!");
        }
    }
#endif

#ifdef WIN32
	void TCPSocket::make_non_blocking() {
		if (!is_blocking) {
			return;
		}
		
		if (sockfd != -1) {
			unsigned long yes{ 1 };
			ioctlsocket(sockfd, FIONBIO, &yes);
			is_blocking = false;
		} else {
			throw std::runtime_error("not connected!");
		}
	}
#endif

#ifdef __linux__
    bool TCPSocket::wait_for_read(long timeout) const{
        pollfd pfd;

        pfd.fd = sockfd;
        pfd.events = POLLIN;
        int result = poll(&pfd, 1, 1000*timeout);

        return result + 1;;
    }
#endif

#ifdef WIN32
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
#endif

#ifdef __linux__
    bool TCPSocket::wait_for_write(long timeout) const{
        pollfd pfd;

        pfd.fd = sockfd;
        pfd.events = POLLOUT;

        int result = poll(&pfd, 1, 1000*timeout);
        return result + 1;
    
    }
#endif

#ifdef WIN32
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
#endif

    void TCPSocket::throw_error(const char* err_msg, int code) const{
        std::string msg{err_msg};
        msg += gai_strerror(code);
        throw std::runtime_error(err_msg);
    }
#ifdef __linux_
    Error TCPSocket::get_last_err() const{
        switch(errno){
            case EWOULDBLOCK:
                return Error::WOULDBLOCK;
            case EINTR:
                return Error::INTERRUPTED;
            default:
                return Error::UNKNOWN;

        }
    }

    std::string TCPSocket::get_last_err_str() const {
        return gai_strerror(errno);
    }
#endif

#ifdef WIN32
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
#endif

}
