/*
 * server_AcceptorWorker.h
 *
 *  Created on: Apr 24, 2016
 *      Author: mastanca
 */

#ifndef SRC_SERVER_SERVER_ACCEPTORWORKER_H_
#define SRC_SERVER_SERVER_ACCEPTORWORKER_H_

#include <string>
#include <vector>

#include "common_Thread.h"
#include "server_ClientProxy.h"
#include "server_MappedData.h"
#include "server_ParsedData.h"

class Socket;

class AcceptorWorker: public Thread {
private:
	// Clients references vector
	std::vector<ClientProxy*> clients;
	// References to launched threads
	std::vector<Thread*> launchedThreads;
	// The main socket from the server, from who we will listen
	Socket* dispatcherSocket;
	// Flag to continue listening
	bool* keepOnListening;
	// The mapped data gathered by my clients
	MappedData* mappedData;
	// The data received and parsed
	ParsedData* parsedData;
public:
	// Constructor
	AcceptorWorker(Socket* dispatcherSocket, bool* keepOnListening,
			MappedData* mappedData, ParsedData* parsedData);
	// Destroyer
	virtual ~AcceptorWorker();
	// Run the worker
	void run();
};

#endif /* SRC_SERVER_SERVER_ACCEPTORWORKER_H_ */
