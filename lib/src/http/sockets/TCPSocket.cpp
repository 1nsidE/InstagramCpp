#include<TCPSocket.h>

namespace Socket {

TCPSocket::TCPSocket(const std::string &host, const std::string &port) {
    connect(host, port);
}

TCPSocket::TCPSocket(int sockfd, bool isBlocking) : m_sockfd{ sockfd }, m_isBlocking{ isBlocking } {}

TCPSocket::TCPSocket(TCPSocket&& tcpSocket) : TCPSocket{-1, false}{
    swap(*this, tcpSocket);
}

TCPSocket::~TCPSocket() {
    TCPSocket::close();
}

TCPSocket &TCPSocket::operator=(TCPSocket &&tcpSocket) {
    m_sockfd = -1;
    m_isBlocking = false;
    
    swap(*this, tcpSocket);
    return *this;
}

void swap(TCPSocket& sock1, TCPSocket& sock2){
    using std::swap;
    swap(sock1.m_sockfd, sock2.m_sockfd);
    swap(sock1.m_isBlocking, sock2.m_isBlocking);
}

}
