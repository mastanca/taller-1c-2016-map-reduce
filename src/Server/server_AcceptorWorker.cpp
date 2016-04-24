/*
 * server_AcceptorWorker.cpp
 *
 *  Created on: Apr 24, 2016
 *      Author: mastanca
 */

#include "server_AcceptorWorker.h"

#define MAX_QUEUE_SIZE 128

AcceptorWorker::~AcceptorWorker() {
}

void AcceptorWorker::run() {
	while(keepOnListening) {
		Socket client;
		dispatcherSocket->accept(&client);
	}
}

AcceptorWorker::AcceptorWorker(Socket* dispatcherSocket, bool* keepOnListening,
		std::vector<std::string>* mappedData) :
		dispatcherSocket(dispatcherSocket), keepOnListening(keepOnListening),
		mappedData(mappedData) {
	dispatcherSocket->listen(MAX_QUEUE_SIZE);
}
