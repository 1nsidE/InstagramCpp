//
// Created by inside on 4/23/16.
//

#ifndef FOLLOGRAPH_TCPSOCKET_H
#define FOLLOGRAPH_TCPSOCKET_H

#include <string>

namespace Socket{

class TCPSocket{
friend class ConnectionListener;
public:
    TCPSocket(const std::string& host, const std::string& port);
    TCPSocket(const TCPSocket& tcp_socket) = delete;
    TCPSocket(TCPSocket&& tcp_socket);
    virtual ~TCPSocket() = default;

    virtual TCPSocket& operator=(TCPSocket&& tcp_socket);

    virtual int write(const void *data, size_t length) const;
    virtual int read(void *data, size_t length) const;
    virtual void close();
    std::string get_ip() const;

    virtual void make_non_blocking();
    virtual bool wait_for_read(long timeout) const;
    virtual bool wait_for_write(long timeout) const;
protected:
    int sockfd;
    bool is_blocking;
private:
    TCPSocket(int _sockfd);
    void connect(const std::string& host, const std::string& port);
    void throw_error(const char* err_msg, int code) const;
};

}

#endif //FOLLOGRAPH_TCPSOCKET_H
