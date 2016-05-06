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

#include "common_Socket.h"
#include "common_Thread.h"
#include "common_Value.h"
#include "server_ClientProxy.h"
#include "server_DayValuesMap.h"

#define MAX_QUEUE_SIZE 128

class Server {
private:
	// Socket for incoming connections
	Socket dispatcherSocket;
	// Reducers vector
	std::vector<Thread*> reducers;
	// Clients vector
	std::vector<ClientProxy*> clients;
	// Reduced data worked by the reducers
	std::vector<std::pair<uint, std::string> > reducedData;
	// The structure containing the distributed received data, sorted by date
	DayValuesMap dayValuesMap;
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
