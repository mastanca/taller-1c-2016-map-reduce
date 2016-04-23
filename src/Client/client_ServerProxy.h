/*
 * client_ServerProxy.h
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#ifndef SRC_CLIENT_CLIENT_SERVERPROXY_H_
#define SRC_CLIENT_CLIENT_SERVERPROXY_H_

#include <string>

#include "../Sockets/common_Socket.h"

class ServerProxy {
private:
	// The actual socket
	Socket socket;
public:
	// Constructor, leaves socket ready to go
	ServerProxy(const std::string& ip, const std::string& port) : socket((char*)ip.c_str(), port.c_str()) {
		socket.connect();
	}
	// Destroyer
	virtual ~ServerProxy();
	// Sends data over the net, through the socket
	void send(const std::string& data);
};

#endif /* SRC_CLIENT_CLIENT_SERVERPROXY_H_ */
