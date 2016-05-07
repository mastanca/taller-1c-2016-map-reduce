/*
 * server_AcceptorWorker.cpp
 *
 *  Created on: Apr 24, 2016
 *      Author: mastanca
 */

#include "server_AcceptorWorker.h"

#include <iterator>
#include <string>
#include <vector>

#include "common_Socket.h"
#include "common_Lock.h"
#include "server_ReceiverWorker.h"

#define MAX_QUEUE_SIZE 128

AcceptorWorker::~AcceptorWorker() {
	// Free clients
	for (std::vector<ClientProxy*>::iterator it = clients.begin();
			it != clients.end(); ++it) {
		delete (*it);
	}
	clients.clear();

	// Free workers
	for (std::vector<Thread*>::iterator it = launchedThreads.begin();
			it != launchedThreads.end(); ++it) {
		delete (*it);
	}
	launchedThreads.clear();
}

void AcceptorWorker::run() {
	while (*keepOnListening) {
		// If there are connections available...
		int availableConnections = dispatcherSocket->select();
		if (availableConnections > 0) {
			for (int i = 0; i < availableConnections; ++i) {
				ClientProxy* client = new ClientProxy;
				clients.push_back(client);
				client->acceptNewConnection(*dispatcherSocket);
				if (client->isConnected()) {
					// Spawn a receiver worker
					// It will call our client proxy's receive method
					ReceiverWorker* receiverWorker = new ReceiverWorker(client,
							mappedData);
					launchedThreads.push_back(receiverWorker);
					receiverWorker->start();
				}
			}
		}
	}

	// We are done listening, so join my children
	for (std::vector<Thread*>::iterator it = launchedThreads.begin();
			it != launchedThreads.end(); ++it) {
		(*it)->join();
	}
}

AcceptorWorker::AcceptorWorker(Socket* dispatcherSocket, bool* keepOnListening,
		MappedData* mappedData) :
		dispatcherSocket(dispatcherSocket), keepOnListening(keepOnListening),
		mappedData(mappedData) {
	dispatcherSocket->listen(MAX_QUEUE_SIZE);
}
