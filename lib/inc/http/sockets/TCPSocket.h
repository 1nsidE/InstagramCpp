//
// Created by inside on 4/23/16.
//

#ifndef FOLLOGRAPH_TCPSOCKET_H
#define FOLLOGRAPH_TCPSOCKET_H

#include <string>

namespace Socket{

    enum class Error{WOULDBLOCK, INTERRUPTED, PIPE_BROKEN, UNKNOWN};
    
    class TCPSocket{
        friend class ConnectionListener;
    public:
        TCPSocket(const std::string& host, const std::string& port);
        TCPSocket(const TCPSocket& tcpSocket) = delete;
        TCPSocket(TCPSocket&& tcpSocket);
        virtual ~TCPSocket();

        virtual TCPSocket& operator=(TCPSocket&& tcpSocket);

        virtual long write(const void *data, size_t length);
        virtual long read(void *data, size_t length);
        virtual void close();
        std::string ip() const;

        virtual void makeNonBlocking();
        virtual bool waitForRead(unsigned int timeout) const;
        virtual bool waitForWrite(unsigned int timeout) const;

        virtual Error lastError() const;
        virtual std::string lastErrorString() const;
    protected:
        int m_sockfd = -1;
        bool m_isBlocking = true;
    private:
        TCPSocket(int sockfd, bool isBlocking);
        void connect(const std::string& host, const std::string& port);
        int lastErrorCode() const;

        friend void swap(TCPSocket& sock1, TCPSocket& sock2);
    };
}

#endif //FOLLOGRAPH_TCPSOCKET_H
