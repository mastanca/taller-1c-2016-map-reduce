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

#include "../Threading/common_Mutex.h"
#include "../Threading/common_Thread.h"
#include "server_ClientProxy.h"

class ReceiverWorker;

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
	std::vector<std::string>* mappedData;
public:
	// Constructor
	AcceptorWorker(Socket* dispatcherSocket, bool* keepOnListening, std::vector<std::string>* mappedData);
	// Destroyer
	virtual ~AcceptorWorker();
	// Run the worker
	void run();
private:
	// Mutex for wrapping
	Mutex mutex;
	// Clients vector push wrapper
	void saveClient(ClientProxy* client);
	// Launched threads push wrapper
	void saveWorker(ReceiverWorker* worker);
};

#endif /* SRC_SERVER_SERVER_ACCEPTORWORKER_H_ */
