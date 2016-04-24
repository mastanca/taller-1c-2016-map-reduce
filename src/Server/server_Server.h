/*
 * server_Server.h
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#ifndef SRC_SERVER_SERVER_SERVER_H_
#define SRC_SERVER_SERVER_SERVER_H_

#include <sys/types.h>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "../MapReduce/common_Value.h"
#include "../Sockets/common_Socket.h"
#include "server_ClientProxy.h"

#define MAX_QUEUE_SIZE 128

class Server {
private:
	// Socket for incoming connections
	Socket dispatcherSocket;
	std::vector<ClientProxy*> clients;
public:
	// Constructor, "" chooses any local ip
	Server(const std::string& port);
	// Destroyer
	virtual ~Server();
	// This method encapsulates the server work
	// and calls the rest of the methods
	void run();
};

#endif /* SRC_SERVER_SERVER_SERVER_H_ */
