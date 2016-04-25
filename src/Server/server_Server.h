/*
 * server_Server.h
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#ifndef SRC_SERVER_SERVER_SERVER_H_
#define SRC_SERVER_SERVER_SERVER_H_

#include <sys/types.h>
#include <string>
#include <utility>
#include <vector>

#include "../Sockets/common_Socket.h"
#include "../Threading/common_Thread.h"
#include "server_ClientProxy.h"

#define MAX_QUEUE_SIZE 128

class Server {
private:
	// Socket for incoming connections
	Socket dispatcherSocket;
	// Reducers vector
	std::vector<Thread*> reducers;
	// Clients vector
	std::vector<ClientProxy*> clients;
	// Mapped data received
	std::vector<std::string> mappedData;
	// Reduced data worked by the reducers
	std::vector<std::pair<uint, std::string> > reducedData;
	// Calls acceptor worker to receive data
	void callAcceptorWorker();
	// Prints results
	void printFinalResults();
	// Joins and frees workers
	void releaseWorkers();
public:
	// Constructor
	explicit Server(const std::string& port);
	// Destroyer
	virtual ~Server();
	// This method encapsulates the server work
	// and calls the rest of the methods
	void run();
};

#endif /* SRC_SERVER_SERVER_SERVER_H_ */
