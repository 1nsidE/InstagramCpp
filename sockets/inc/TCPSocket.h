//
// Created by inside on 4/23/16.
//

#ifndef FOLLOGRAPH_TCPSOCKET_H
#define FOLLOGRAPH_TCPSOCKET_H

#include <string>

namespace Socket{

    enum class Error{WOULDBLOCK, INTERRUPTED, UNKNOWN};

    class TCPSocket{
        friend class ConnectionListener;
    public:
        TCPSocket(const std::string& host, const std::string& port);
        TCPSocket(const TCPSocket& tcp_socket) = delete;
        TCPSocket(TCPSocket&& tcp_socket);
        virtual ~TCPSocket();

        virtual TCPSocket& operator=(TCPSocket&& tcp_socket);

        virtual long write(const void *data, size_t length);
        virtual long read(void *data, size_t length);
        virtual void close();
        std::string get_ip() const;

        virtual void make_non_blocking();
        virtual bool wait_for_read(long timeout) const;
        virtual bool wait_for_write(long timeout) const;

        virtual Error get_last_err() const;
        virtual std::string get_last_err_str() const;
    protected:
        int sockfd = -1;
        bool is_blocking = true;
    private:
        TCPSocket(int _sockfd, bool is_blocking_);
        void connect(const std::string& host, const std::string& port);
        int last_err_code();
        [[noreturn]] void throw_error(const char* err_msg, int code) const;

        #ifdef WIN32
        void init_wsa();
        #endif  
    };

}

#endif //FOLLOGRAPH_TCPSOCKET_H
