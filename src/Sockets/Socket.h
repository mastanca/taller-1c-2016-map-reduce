/*
 * Socket.h
 *
 *  Created on: Apr 17, 2016
 *      Author: mastanca
 */

#ifndef SRC_SOCKETS_SOCKET_H_
#define SRC_SOCKETS_SOCKET_H_

#include <string>

struct addrinfo;

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif

class Socket {
private:
	int fd;
	struct addrinfo* result;
public:
	// Initiates with given parameters
	Socket(std::string hostname, std::string port);
	// Free's socket resources
	virtual ~Socket();
	// Binds the socket to a connection
	int bind();
	// Listens for new connections, up to max queue size (blocker)
	int listen(int maxQueueSize);
	// Accepts new connection, returns connection fd in Client's fd
	int accept(Socket* client);
	// Connects to server (blocker)
	int connect();
	// Receives size bytes from the net
	int receive(std::string* buffer, int size);
	// Sends size bytes over the net
	int send(std::string* buffer, int size);
};

#endif /* SRC_SOCKETS_SOCKET_H_ */
