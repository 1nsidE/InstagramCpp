//
// Created by inside on 4/10/16.
//

#ifndef HTTPSERVER_SERVERSOCKET_H
#define HTTPSERVER_SERVERSOCKET_H

#include <memory>
#include "TCPSocket.h"

namespace Socket{

	class ConnectionListener{
	public:
		ConnectionListener(unsigned int _port);
		ConnectionListener(const ConnectionListener& connection_listener) = delete;
		ConnectionListener(ConnectionListener&& connections_listener);
		~ConnectionListener();

		TCPSocket wait();
		void close();
		void make_non_blocking();
	private:
		void init();
		TCPSocket blocking_wait();
		TCPSocket nonblocking_wait();

		int server_sockfd = -1;
		unsigned int port = 0;
		bool is_blocking = true;
	};

}
#endif //HTTPSERVER_SERVERSOCKET_H
